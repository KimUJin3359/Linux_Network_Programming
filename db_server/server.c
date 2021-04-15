#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

static struct sockaddr_in addr = {0};
static struct sockaddr new_addr;
// socket File Descriptor
static int fd;
static int new_fd;
// database File Descriptor
static FILE *db_fd;

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
	shutdown(new_fd, SHUT_WR);
	// cancel thread
    write(1, "DB SERVER CLOSED...\n", 20);
	// close socket
	close(new_fd);
    close(fd);
    exit(1);
}

int open_file()
{
	int retry = 0;

	// open file
	while (!(db_fd = fopen("./db/database.txt", "a+")))
	{
		retry++;
		if (retry == 10)
		{
			write(new_fd, "Sorry.. Can't open Database System...\n", 38);
			return (1);
		}
		write(new_fd, "Trying to open...\n", 18);
		sleep(1);
	}
	return (0);
}

int main()
{
	// ctrl c
    signal(SIGINT, sig_exit);

    char buf[128];
    // socket init
    int ret = socket_init();
	int len;

    if (ret == -1)
    {
        write(1, "INIT ERROR\n", 11);
        exit(0);
    }
	new_fd = accept(fd, &new_addr, &len);
	write(1, "DB START\n", 9);

	// when message come, run command
    while (1) 
    {
		int size;
		char file[128];

        memset(buf, 0, sizeof(buf));
		size = read(new_fd, buf, sizeof(buf));
		printf("%s", buf);
		// exec command
        if (size > 0)
		{
			// save cmd
			if (strlen(buf) >= 5 && strncmp(buf, "save ", 5) == 0)
			{
				if (open_file())
					exit(0);
				fputs(buf + 5, db_fd); 
				write(new_fd, "SAVE OK\n", 8);
				fclose(db_fd);
			}
			// read cmd
			else if (strlen(buf) >= 5 && strncmp(buf, "read ", 5) == 0)
			{
				char content[128];
				char *f_key;
				char *f_cont;
				int find = 0;


				buf[strlen(buf) - 1] = '\0';
				if (open_file())
					exit(0);
				while (fgets(file, sizeof(file), db_fd) != NULL)
				{
					f_key = strtok(file, ":");
					if (strlen(f_key) != 0 && strncmp(buf + 5, f_key, strlen(f_key)) == 0)
					{
						memset(content, 0, sizeof(content));
						f_cont = strtok(NULL, ":");
						strcpy(content, f_cont);
						find = 1;
					}
					memset(file, 0, sizeof(file));
				}
				// write value
				if (!find)
					write(new_fd, "No key in DB\n", 13);
				else
					write(new_fd, content, strlen(content));
				fclose(db_fd);
			}
			// read clear
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
			write(1, "DB SERVER CLOSED...\n", 20);
			sleep(3);
			execl("./main", 0);
		}
        usleep(1000 * 500);
    }
    return 0;
}
