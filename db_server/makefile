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
	rm -rf *.o

fclean : clean
	rm ${TARGET}

re : fclean re

.PHONY : all clean fclean re
