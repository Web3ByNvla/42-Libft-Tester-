NAME = test
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ../Libft_42
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR)/includes

all: $(NAME)

$(NAME): test.c $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) test.c $(LIBFT) -o $(NAME)

$(LIBFT): $(wildcard $(LIBFT_DIR)/srcs/*.c) $(LIBFT_DIR)/includes/libft.h
	$(MAKE) -C $(LIBFT_DIR)

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all run clean fclean re
