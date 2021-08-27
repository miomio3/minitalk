NAME = ft_client.out ft_server.out
CC = gcc
FLUG = -Wall -Wextra -Werror
SRC = *.c

all		:$(NAME)
%.out	:%.c
	$(CC) $(FLUG) $< share.c -o $@
clean	:
	rm -f $(NAME)
fclean	:
	rm -f $(NAME)
re		:fclean clean all

.PHONY		:all clean fclean re