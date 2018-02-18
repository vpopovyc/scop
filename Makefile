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

CCFLAGS = -Wall -Wextra -Werror -O3

FRMPATH = -F /Library/Frameworks

# -----------------------------------------------------------
# Frameworks

FRAMEWORKS = -framework OpenGL -framework SDL2

# -----------------------------------------------------------
# Libraries

# libGLEW

LIBGLEWBIN = libglew/src/lib/libGLEW.a

LIBGLEWINC = libglew/src/include

LIBGLEW = libglew/src/lib

# libFT

LIBFTBIN = libft/libFT.a

LIBFTINC = libft/include

LIBFT = libft

# -----------------------------------------------------------
# Compiler rules

LIBS = -lGLEW -lFT

LIBSDIR = -L$(LIBGLEW) -L$(LIBFT)

LIBSINC = -I$(LIBGLEWINC) -I$(LIBFTINC)

# -----------------------------------------------------------

all: $(EXEC)

$(EXEC): $(LIBFTBIN) $(LIBGLEWBIN) $(OBJ)
	$(CC) $(CCFLAGS) $(FRMPATH) $(FRAMEWORKS) $(LIBSDIR) $(LIBS) \
	$(OBJ) -o $(EXEC)

$(LIBFTBIN): libft.all

$(LIBGLEWBIN): glew.all

%.o: %.c
	$(CC) -g $(CCFLAGS) $(LIBSINC) $(FRMPATH) -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(EXEC)

re: glew.clean libft.fclean fclean all

libft.all:
	@echo  "\x1b[32mlibft   compiles...\x1b[0m"
	@make -C libft/ all

libft.clean:
	@make -C libft/ clean

libft.fclean:
	@make -C libft/ fclean

libft.re:
	@make -C libft re

glew.all:
	@echo  "\x1b[32mlibglew   compiles...\x1b[0m"
	@make -C libglew/src glew.lib.static

glew.clean:
	@make -C libglew/src distclean

.phony: all clean fclean re
