#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// when SIGINT or input exit cmd, thread cancel and retrurn
void						sig_exit();
// socket run
void						socket_run(char buf[128]);

extern int					fd;
extern pthread_t			tid;
extern struct sockaddr_in	addr;

int main()
{
    char buf[128];
	
	// ctrl c input
    signal(SIGINT, sig_exit);
	while (1) 
    {
		// while input connect
		write(1, "SHELL >> ", 9);
		fgets(buf, sizeof(buf), stdin);
		// eliminate new line char
		buf[strlen(buf) - 1] = '\0';
		// connect + ' '(8 characters) + IP Address
		if (strlen(buf) >= 8 && strncmp(buf, "connect ", 8) == 0)
			socket_run(buf);
		else if(strcmp(buf, "exit") == 0)
			exit(0);
    }
	// not any case, come to return
    return (0);
}
