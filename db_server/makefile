CC = gcc
CFLAGS = -Wall -Wextra

TARGET = server

SRCS = server.c server_utils.c
OBJS = ${SRCS:.c=.o}

${TARGET} :${OBJS}
	${CC} -o $@ $^

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ./

all : ${TARGET}

clean :
	rm *.o

fclean : clean
	rm ${TARGET}

re : fclean all

.PHONY : all clean fclean re
