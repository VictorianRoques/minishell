NAME = minishell
CC = clang
SRC = srcs/main.c srcs/utils/utils.c srcs/parser/build_args.c srcs/parser/build_builtin.c \
		srcs/parser/build_command.c srcs/parser/build_filename.c srcs/parser/build_job.c \
		srcs/parser/build_line.c srcs/parser/parser.c srcs/executor/execute.c \
		srcs/executor/execute_bin.c srcs/executor/path.c srcs/executor/pipe.c srcs/executor/redirection.c \
		srcs/ast_tree/ast_tree.c srcs/lexer/lexer.c srcs/lexer/create_tokens.c

CFLAGS = -Wall -Werror -Wextra
OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o ${<:.c=.o}

all: $(NAME)

$(NAME): $(OBJ)
		make -C libft
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a

deubg: $(CFLAGS) += -g3
debug: re

santize: $(CFLAGS) += -fsanitize=address
sanitize: debug

clean: 
		make -C libft clean
		rm -rf $(OBJ)

fclean: clean
		make -C libft fclean
		rm -rf $(NAME)

re: fclean all