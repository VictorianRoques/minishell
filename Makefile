# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/26 17:06:32 by fmanetti          #+#    #+#              #
#    Updated: 2021/04/08 17:20:46 by fmanetti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minish

FILES		=	minishell.c							\
				read/read.c							\
				read/check_keys.c					\
				read/str_print_and_handle.c			\
				read/get_next_separator.c			\
				read/heredoc.c						\
				read/multilines.c					\
				lexe/lexer.c						\
				lexe/create_tokens.c				\
				lexe/split_separator.c 				\
				lexe/split_separator_utils.c 		\
				lexe/sort.c 						\
				lexe/sort_utils.c 					\
				lexe/lexe_utils.c 					\
				lexe/check_tokens.c 				\
				lexe/add_word.c 					\
				lexe/sort_heredoc_wild.c 			\
				lexe/sort_spaces_quotes.c 			\
				parse/env_path_parser.c				\
				parse/lists/t_access.c				\
				parse/lists/list_sort_env.c			\
				parse/split/split_var.c				\
				parse/split/split_keep.c			\
				parse/build/args.c					\
				parse/build/builtin.c				\
				parse/build/command.c				\
				parse/build/command2.c 				\
				parse/build/job.c					\
				parse/build/line.c					\
				parse/parser.c						\
				parse/check_parse_utils.c 			\
				parse/vars.c						\
				wildcard/star_to_str.c				\
				wildcard/list_sort_files.c			\
				wildcard/starcmp.c					\
				wildcard/wild_lists.c				\
				wildcard/wildcard.c					\
				keys/arrows.c						\
				keys/control.c						\
				keys/delete.c						\
				keys/home_end.c						\
				keys/move_word_or_column.c			\
				keys/keys_utils.c					\
				history/init_history.c				\
				history/history.c					\
				history/make_history.c				\
				execute/path.c						\
				execute/signals_term.c				\
				execute/execute.c					\
				execute/execute_pipe_utils.c 		\
				execute/execute_bin.c				\
				execute/create_cmd_table.c 			\
				execute/exit_status.c				\
				execute/redirection.c				\
				execute/change_data.c				\
				builtins/builtins.c					\
				builtins/ft_echo.c					\
				builtins/ft_cd.c					\
				builtins/ft_pwd.c					\
				builtins/ft_export.c				\
				builtins/ft_unset.c					\
				builtins/ft_env.c					\
				builtins/ft_exit.c					\
				ast_tree/ast_tree.c					\
				ast_tree/create_node.c 				\
				errors_and_free/error.c				\
				errors_and_free/free.c

HFILES		=	minishell.h							\
				struct.h							\
				macros.h					

LIB			=	libft.a

SOURCE		=	$(addprefix ./srcs/, $(FILES))
HEADERS		=	$(addprefix ./include/, $(HFILES))
INCLUDE		=	$(addprefix ./include/libft/, $(LIB))

OBJ			=	$(SOURCE:%.c=%.o)

CC			= 	clang

CFLAGS		=   -I include/ -Wall -Wextra -Werror
FSANITIZE	= 	-g3 -O0 -fsanitize=address

RED			=	\033[0;31m
GREEN		=	\033[0;32m
WHITE		=	\033[0m

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS) $(INCLUDE)
	@printf "[ $(NAME) ] Compiling...\r"
	@($(CC) -o $(NAME) $(SOURCE) $(INCLUDE) $(CFLAGS))
	@printf "${GREEN}"
	@printf "                          iiii                     iiii                  hhhhhhh                                lllllll lllllll  \n"
	@printf "                         i::::i                   i::::i                 h:::::h                                l:::::l l:::::l  \n"
	@printf "                          iiii                     iiii                  h:::::h                                l:::::l l:::::l  \n"
	@printf "                                                                         h:::::h                                l:::::l l:::::l  \n"
	@printf "   mmmmmmm    mmmmmmm   iiiiiiinnnn  nnnnnnnn    iiiiiii     ssssssssss   h::::h hhhhh           eeeeeeeeeeee    l::::l  l::::l  \n"
	@printf " mm:::::::m  m:::::::mm i:::::in:::nn::::::::nn  i:::::i   ss::::::::::s  h::::hh:::::hhh      ee::::::::::::ee  l::::l  l::::l  \n"
	@printf "m::::::::::mm::::::::::m i::::in::::::::::::::nn  i::::i ss:::::::::::::s h::::::::::::::hh   e::::::eeeee:::::eel::::l  l::::l  \n"
	@printf "m::::::::::::::::::::::m i::::inn:::::::::::::::n i::::i s::::::ssss:::::sh:::::::hhh::::::h e::::::e     e:::::el::::l  l::::l  \n"
	@printf "m:::::mmm::::::mmm:::::m i::::i  n:::::nnnn:::::n i::::i  s:::::s  ssssss h::::::h   h::::::he:::::::eeeee::::::el::::l  l::::l  \n"
	@printf "m::::m   m::::m   m::::m i::::i  n::::n    n::::n i::::i    s::::::s      h:::::h     h:::::he:::::::::::::::::e l::::l  l::::l  \n"
	@printf "m::::m   m::::m   m::::m i::::i  n::::n    n::::n i::::i       s::::::s   h:::::h     h:::::he::::::eeeeeeeeeee  l::::l  l::::l  \n"
	@printf "m::::m   m::::m   m::::m i::::i  n::::n    n::::n i::::i ssssss   s:::::s h:::::h     h:::::he:::::::e           l::::l  l::::l  \n"
	@printf "m::::m   m::::m   m::::mi::::::i n::::n    n::::ni::::::is:::::ssss::::::sh:::::h     h:::::he::::::::e         l::::::ll::::::l \n"
	@printf "m::::m   m::::m   m::::mi::::::i n::::n    n::::ni::::::is::::::::::::::s h:::::h     h:::::h e::::::::eeeeeeee l::::::ll::::::l \n"
	@printf "m::::m   m::::m   m::::mi::::::i n::::n    n::::ni::::::i s:::::::::::ss  h:::::h     h:::::h  ee:::::::::::::e l::::::ll::::::l \n"
	@printf "mmmmmm   mmmmmm   mmmmmmiiiiiiii nnnnnn    nnnnnniiiiiiii  sssssssssss    hhhhhhh     hhhhhhh    eeeeeeeeeeeeee llllllllllllllll \n"
	@printf "${WHITE}"
	@printf "┏┓ ╻ ╻   ┏━╸┏┳┓┏━┓┏┓╻┏━╸╺┳╸╺┳╸╻   ┏┓     ╻ ╻╻┏━┓┏━┓┏━┓╻ ╻┏━╸┏━┓     ┏━╸┏━┓┏┳┓┏━┓╻╻  ┏━╸╺┳┓  ${GREEN}┏━┓╻ ╻┏━╸┏━╸┏━╸┏━┓┏━┓┏━╸╻ ╻╻  ╻  ╻ ╻\n${WHITE}"
	@printf "┣┻┓┗┳┛   ┣╸ ┃┃┃┣━┫┃┗┫┣╸  ┃  ┃ ┃   ┃╺╋╸   ┃┏┛┃┣┳┛┃ ┃┃┓┃┃ ┃┣╸ ┗━┓     ┃  ┃ ┃┃┃┃┣━┛┃┃  ┣╸  ┃┃  ${GREEN}┗━┓┃ ┃┃  ┃  ┣╸ ┗━┓┗━┓┣╸ ┃ ┃┃  ┃  ┗┳┛\n${WHITE}"
	@printf "┗━┛ ╹    ╹  ╹ ╹╹ ╹╹ ╹┗━╸ ╹  ╹ ╹   ┗━┛    ┗┛ ╹╹┗╸┗━┛┗┻┛┗━┛┗━╸┗━┛     ┗━╸┗━┛╹ ╹╹  ╹┗━╸┗━╸╺┻┛  ${GREEN}┗━┛┗━┛┗━╸┗━╸┗━╸┗━┛┗━┛╹  ┗━┛┗━╸┗━╸ ╹ \n${WHITE}"

lib:
	@make re bonus -C include/libft
	@make clean -C include/libft

clean:
	@/bin/rm -f $(OBJ)
	@printf "Object files ${RED}removed\n${WHITE}"

fclean: clean
	@/bin/rm -rf $(NAME)*
	@/bin/rm -rf .vscode .minish_history
	@printf "[ $(NAME) ] ${RED}removed\n${WHITE}"

re: fclean all

.PHONY: all clean fclean re

.SILENT:
