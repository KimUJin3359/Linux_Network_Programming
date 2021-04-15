#include "client.h"

int					fd;
struct sockaddr_in	addr;
pthread_t			tid;

// socket init with given address
int socket_init(char *str) 
{
    int ret = 0;

    // socket input
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) 
		return (-1);
    // using IPv4, port : 12345, ip address : (input)
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = inet_addr(str);
	// connect to socket
    ret = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
	// when failed
    if (ret == -1) 
		return (ret);
    return (ret);
}

// when SIGINT or input exit cmd, thread cancel and return
void sig_exit()
{
	// send \0 to server
	shutdown(fd, SHUT_WR);
	// cancel thread
	pthread_cancel(tid);
	pthread_join(tid, NULL);
    write(1, "DB ENDED\n", 9);
	// close socket
    close(fd);
    exit(0);
}


// send user input to server
void *socket_write(void *ptr)
{
	char buf[128];

	while (TRUE)
	{
		memset(buf, 0, sizeof(buf));
		// if user input a cmd
		if (read(0, buf, sizeof(buf)) > 0)
		{
			write(1, "CLIENT >> ", 10);
			write(1, buf, strlen(buf));
			// if user input exit 
			if (strncmp(buf, "exit", 4) == 0)
				sig_exit();
			// else send cmd to server
			write(fd, buf, strlen(buf));
		}
		usleep(1000 * 500);
	}
}

// socket run
void socket_run(char buf[128])
{
	// except 'connect ' + ip adrress
	int ret = socket_init(buf + 8);

	if (ret == -1)
	{
		write(1, "INIT ERROR\n", 11);
		exit(0);
	}
	sleep(1);
	write(1, "DB START\n", 9);
	// socket write start
	pthread_create(&tid, NULL, socket_write, NULL);
	// when message come, print it to host's window
	while (TRUE)
	{
		int size;

		memset(buf, 0, 128);
		size = read(fd, buf, 128);
		// print it
		if (size > 0)
			write(1, buf, strlen(buf));
		// when shutdown come, exit program
		else if (size == 0)
			sig_exit();
		usleep(1000 * 500);
	}
}
