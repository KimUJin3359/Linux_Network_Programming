CC = gcc
CFLAGS = -Wall -Wextra

TARGET = client

SRCS = client.c client_utils.c
OBJS = ${SRCS:.c=.o}

${TARGET} :${OBJS}
	${CC} -o $@ $^ -lpthread

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ./ -lpthread

all : ${TARGET}

clean :
	rm *.o

fclean : clean
	rm ${TARGET}

re : fclean all

.PHONY : all clean fclean re
