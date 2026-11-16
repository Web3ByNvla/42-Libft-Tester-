NAME = test
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ../Libft_novella
LIBFT_SRCS = $(wildcard $(LIBFT_DIR)/ft_*.c)
INCLUDES = -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): test.c $(LIBFT_SRCS) $(LIBFT_DIR)/libft.h
	$(CC) $(CFLAGS) $(INCLUDES) test.c $(LIBFT_SRCS) -o $(NAME)

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all run clean fclean re
