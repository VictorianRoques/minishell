# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/11 17:50:17 by fmanetti          #+#    #+#              #
#    Updated: 2021/04/06 17:31:55 by fmanetti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

FILES	=	ft_arrlen.c			\
			ft_atof.c			\
			ft_atoi.c			\
			ft_bzero.c			\
			ft_calloc.c			\
			ft_free_array.c		\
			ft_isalnum.c		\
			ft_isalpha.c		\
			ft_isascii.c		\
			ft_isdigit.c		\
			ft_isprint.c		\
			ft_isspace.c		\
			ft_itoa.c			\
			ft_memalloc.c		\
			ft_memccpy.c		\
			ft_memchr.c			\
			ft_memcmp.c			\
			ft_memcpy.c			\
			ft_memdel.c			\
			ft_memmove.c		\
			ft_memset.c			\
			ft_merge.c			\
			ft_print_array.c	\
			ft_putchar.c		\
			ft_putchar_fd.c		\
			ft_putendl_fd.c		\
			ft_putnbr.c			\
			ft_putnbr_fd.c		\
			ft_putstr.c			\
			ft_putstr_fd.c		\
			ft_sort_array.c		\
			ft_split.c			\
			ft_strcat.c			\
			ft_strchr.c			\
			ft_strcmp.c			\
			ft_strcpy.c			\
			ft_strdup.c			\
			ft_strjoin.c		\
			ft_strjoin_nl.c		\
			ft_strjoin_ln.c		\
			ft_strlcat.c		\
			ft_strlcpy.c		\
			ft_strlen.c			\
			ft_strmapi.c		\
			ft_strncat.c		\
			ft_strncmp.c		\
			ft_strncpy.c		\
			ft_strnstr.c		\
			ft_strrchr.c		\
			ft_strstr.c			\
			ft_strtrim.c		\
			ft_substr.c			\
			ft_swap.c			\
			ft_tolower.c		\
			ft_toupper.c		\
			get_next_line.c

BFILES	=	ft_lstnew.c			\
			ft_lstadd_front.c	\
			ft_lstsize.c		\
			ft_lstlast.c		\
			ft_lstadd_back.c	\
			ft_lstdelone.c		\
			ft_lstclear.c		\
			ft_lstiter.c		\
			ft_lstmap.c 

HEADERS	=	libft.h

SOURCE	=	$(addprefix ./srcs/, $(FILES))
BONUS	=	$(addprefix ./srcs/, $(BFILES))

OBJ		=	$(SOURCE:%.c=%.o)

OBJB	=	$(BONUS:%.c=%.o) $(OBJ)

CC		= 	clang
CFLAGS 	=	-Wall -Wextra -Werror -I .

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	@ar rc $(NAME) $^
	@ranlib $(NAME)
	@printf "[ $(NAME) ] Created \033[0;32mSuccessfully\n\033[0m" $(SUCCESS)

bonus: all $(OBJB)
	@ar rc $(NAME) $(OBJB)
	@ranlib $(NAME)
	@printf "[ $(NAME) + bonus] Created \033[0;32mSuccessfully\n\033[0m" $(SUCCESS)

clean:
	@/bin/rm -f $(OBJ) $(OBJB)
	@printf "Object files \033[0;31mremoved\n\033[0m"

fclean: clean
	@/bin/rm -f $(NAME)
	@printf "[ $(NAME) ] \033[0;31mremoved\n\033[0m"

re: fclean all

.PHONY: all bonus clean fclean re

.SILENT:
