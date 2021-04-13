#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

static struct sockaddr_in addr = {0};
static struct sockaddr new_addr;
static int fd;
static int new_fd;
static pthread_t tid;

int socket_init() 
{
    int ret = 0;

    //1. socket
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
		return (-1);

    //2. connect - bind & listen
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = 0;
    ret = bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
    if (ret == -1) 
		return (ret);
    ret = listen(fd,2);
    if (ret == -1) 
		return (ret);
    return (ret);
}

// when SIGINT, thread cancel and return
void sig_exit()
{
	// send \0 to client
	shutdown(fd, SHUT_WR);
	// cancel thread
    pthread_cancel(tid);
    pthread_join(tid, NULL);
    write(1, "CHATTING ROOM CLOSED\n", 21);
	// close socket
	close(new_fd);
    close(fd);
    exit(1);
}

// send user input to a client
void *socket_write(void *ptr)
{
    char buf[128];
    
	while (1)
    {
        memset(buf, 0, sizeof(buf));
		if (read(0, buf, sizeof(buf)) > 0)
        	write(new_fd, buf, strlen(buf));
        usleep(1000 * 500);
    }
}


int main()
{
	// ctrl c
    signal(SIGINT, sig_exit);

    char buf[128];
    // socket init
    int ret = socket_init();
	int len;

	write(1, "PROGRAM START\n", 14);
    if (ret == -1)
    {
        write(1, "INIT ERROR\n", 11);
        exit(0);
    }
	new_fd = accept(fd, &new_addr, &len);
	write(1, "CHATTING ROOM OPEN\n", 19);
	// socket write start
    pthread_create(&tid, NULL, socket_write, NULL);
    // when message come, print it to host's window
    while (1) 
    {
		int size;

        memset(buf, 0, sizeof(buf));
		size = read(new_fd, buf, sizeof(buf));
		// print
        if (size > 0)
            write(1, buf, strlen(buf));
		// when shutdown
		else if (size == 0)
		{
			// close socket
			close(fd);
			close(new_fd);
			// cancel thread
			pthread_cancel(tid);
			pthread_join(tid, NULL);
			// when socket freed, take a time to restart
			write(1, "CHATTING ROOM CLOSED\n", 21);
			sleep(3);
			execl("./main", 0);
		}
        usleep(1000 * 500);
    }
    return 0;
}
