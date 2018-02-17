# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/01 18:32:39 by vpopovyc          #+#    #+#              #
#    Updated: 2017/11/01 20:47:24 by vpopovyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = scop

CORE = src/scop.c src/handle_command.c src/globals.c src/sdl_gl_init.c \
        src/parse_obj.c src/loader.c src/utils/stack.c src/utils/context.c \
        src/compile_shaders.c

SRC += $(CORE)

OBJ = $(SRC:.c=.o)

CC = clang
CCFLAGS = -Wall -Wextra -Werror
FWPATH = -F /Library/Frameworks
FRAMEWORKS = -framework OpenGL /Users/vpopovyc/.brew/lib/libGLEW.dylib -framework SDL2 libft/libft.a 

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CCFLAGS) $(FWPATH) $(FRAMEWORKS) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) -g -I/Users/vpopovyc/.brew/include -Ilibft/libft.h $(CCFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(EXEC)

re: fclean all

.phony: all clean fclean re
	
