# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/15 17:08:37 by vpopovyc          #+#    #+#              #
#    Updated: 2017/09/16 16:46:52 by vpopovyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_itoa.c ft_atof.c ft_memcpy.c ft_memset.c ft_strcat.c ft_strchr.c \
	ft_strcpy.c ft_strncpy.c ft_strjoin.c ft_strnew.c ft_strdup.c ft_ppdel.c \
	ft_strequ.c ft_strsplit.c get_next_line.c ft_strlen.c matrices.c \
	quaternions.c quaternions_ext.c ft_split.c ft_atoi.c ft_is_empty.c

INC = libft.h

OBJ = $(SRC:.c=.o) 

CFLAGS = -c -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo  "\x1b[32mlibft   compiled\x1b[0m"

%.o: %.c
	clang -I $(INC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all