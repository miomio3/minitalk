NAME = ft_client.out ft_server.out
CC = gcc
FLUG = -Wall -Wextra -Werror
SRC = *.c

all		:$(NAME)
%.out	:%.c share.c share2.c
	$(CC) $(FLUG) $< share.c share2.c -o $@
clean	:
	rm -f $(NAME)
fclean	:
	rm -f $(NAME)
re		:fclean clean all

.PHONY		:all clean fclean re