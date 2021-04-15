#include "server.h"

struct sockaddr_in	addr = { 0 };
struct sockaddr		new_addr;
// socket File Descriptor
int					fd;
int					new_fd;
// database File Descriptor
FILE				*db_fd;

// socket init
int socket_init() 
{
    int ret = 0;

    // IPv4, Bidirection
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
		return (-1);

    // IPv4, Port Number : 12345, addr 0 -> host
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.s_addr = 0;
    ret = bind(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
    if (ret == -1) 
		return (ret);
	// wait until client comes
    ret = listen(fd,2);
    if (ret == -1) 
		return (ret);
    return (ret);
}

// when SIGINT, thread cancel and return
void sig_exit()
{
	// exit session
	shutdown(new_fd, SHUT_WR);
    write(1, "DB SERVER CLOSED...\n", 20);
	// close socket
	close(new_fd);
    close(fd);
    exit(0);
}

// access Database named database.txt
int open_file()
{
	// count for database system
	int retry = 0;

	// open file with read, write at the end of a file
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

// run when cmd save
void save_command(char buf[128])
{
	if (open_file())
		exit(0);
	// write to database
	fputs(buf + 5, db_fd); 
	// response to client
	write(new_fd, "SAVE OK\n", 8);
	// close the database
	fclose(db_fd);
}

// run when cmd read
void read_command(char buf[128])
{
	// file buffer
	char file[128];
	char ret[128];
	// key, value in database
	char *f_key;
	char *f_val;
	// if find or not
	int find = 0;

	// delete new line in command
	buf[strlen(buf) - 1] = '\0';
	// access to database
	if (open_file())
		exit(0);
	// read a data from database
	while (fgets(file, sizeof(file), db_fd) != NULL)
	{
		// key in database in each line
		f_key = strtok(file, ":");
		// compare with input key and file key
		if (strlen(f_key) == strlen(buf + 5) && strncmp(buf + 5, f_key, strlen(f_key)) == 0)
		{
			f_val = strtok(NULL, ":");
			strcpy(ret, f_val);
			find = 1;
		}
		memset(file, 0, sizeof(file));
	}
	// write value
	if (!find)
		write(new_fd, "No key in DB\n", 13);
	else
		write(new_fd, ret, strlen(ret));
	// close the database
	fclose(db_fd);
}


