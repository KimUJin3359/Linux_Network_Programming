#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

extern struct sockaddr_in	addr;
extern struct sockaddr		new_addr;
// socket File Descriptor
extern int					fd;
extern int					new_fd;
// database File Descriptor
extern FILE					*db_fd;

// socket init
int							socket_init();
// when SIGINT or input exit cmd, thread cancel and return
void						sig_exit();
// access Database named database.txt
int							open_file();
void						save_command(char buf[128]);
void						read_command(char buf[128]);
int							accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

int main()
{
    char buf[128];
    // socket init
    int ret = socket_init();
	int len;

    signal(SIGINT, sig_exit);
    if (ret == -1)
    {
        write(1, "INIT ERROR\n", 11);
        exit(0);
    }
	new_fd = accept(fd, &new_addr, &len);
	write(1, "CLIENT ACCESS\n", 14);

	// when message come, run command
    while (1) 
    {
		int size;

        memset(buf, 0, sizeof(buf));
		size = read(new_fd, buf, sizeof(buf));
		// exec command
        if (size > 0)
		{
			write(1, "CLIENT >> ", 10);
			write(1, buf, strlen(buf));
			// save cmd
			if (strlen(buf) >= 5 && strncmp(buf, "save ", 5) == 0)
				save_command(buf);
			// read cmd
			else if (strlen(buf) >= 5 && strncmp(buf, "read ", 5) == 0)
				read_command(buf);
			// clear cmd
			else if (strlen(buf) == 6 && strcmp(buf, "clear\n") == 0)
			{
				system("rm ./db/database.txt");
				write(new_fd, "CLEAR OK\n", 9);
			}
		}
		// when shutdown
		else if (size == 0)
		{
			// close socket
			close(fd);
			close(new_fd);
			// when socket freed, take a time to restart
			write(1, "CLIENT DISCONNECTED\n", 20);
			sleep(3);
			execl("./server", 0);
		}
        usleep(1000 * 500);
    }
	// not any case, to arrive here
    return (0);
}
