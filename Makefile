NAME = minishell
CC = clang
SRC = srcs/main.c
CFLAGS = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
		make -C libft
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a

deubg: CFLAGS += -g3
debug: re

santize: CFLAGS += fsanitize=address -g3
sanitize: debug

clean: 
		make -C libft clean
		rm -rf $(OBJ)

fclean: clean
		make -C libft fclean
		rm -rf $(NAME)

re: fclean all