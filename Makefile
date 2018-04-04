# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/01 18:32:39 by vpopovyc          #+#    #+#              #
#    Updated: 2018/04/04 20:45:50 by vpopovyc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

EXEC = scop

CORE = src/scop.c src/handle_command.c src/sdl_gl_init.c src/parse_obj.c \
		src/loader.c src/utils/delims.c src/utils/context.c \
        src/compile_shaders.c src/view_update.c src/draw.c src/skybox.c \
		src/textures.c src/loader_addition.c src/utils/buffer_attribs.c \
		src/parse_obj_addition.c

SRC += $(CORE)

OBJ = $(SRC:.c=.o)

CC = clang

CCFLAGS = -Wall -Wextra -Werror -O3

FRMPATH = -F /Library/Frameworks

SCOPINC = -Iincludes -Isrc/utils

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

# libLodePNG

LIBLODEPNGBIN = liblodepng/libLodePNG.a

LIBLODEINC = liblodepng

LIBLODEPNG = liblodepng

# -----------------------------------------------------------
# Compiler rules

LIBS = -lGLEW -lFT -lLodePNG

LIBSDIR = -L$(LIBGLEW) -L$(LIBFT) -L$(LIBLODEPNG)

LIBSINC = -I$(LIBGLEWINC) -I$(LIBFTINC) -I$(LIBLODEINC)

# -----------------------------------------------------------

all: $(EXEC)

$(EXEC): $(LIBFTBIN) $(LIBGLEWBIN) $(LIBLODEPNGBIN) $(OBJ)
	$(CC) $(CCFLAGS) $(FRMPATH) $(FRAMEWORKS) $(LIBSDIR) $(LIBS) \
	$(OBJ) -o $(EXEC)

$(LIBFTBIN): libft.all

$(LIBGLEWBIN): glew.all

$(LIBLODEPNGBIN): lode.all

%.o: %.c
	$(CC) $(CCFLAGS) $(SCOPINC) $(LIBSINC) $(FRMPATH) -o $@ -c $<

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(EXEC)

re: lode.fclean glew.clean libft.fclean fclean all

libft.all:
	@echo  "\x1b[32mlibft   compiles...\x1b[0m"
	@make -C libft/ all

libft.clean:
	@make -C libft/ clean

libft.fclean:
	@make -C libft/ fclean

libft.re:
	@make -C libft/ re

glew.all:
	@echo  "\x1b[32mlibglew   compiles...\x1b[0m"
	@make -C libglew/src glew.lib.static

glew.clean:
	@make -C libglew/src distclean

lode.all:
	@echo  "\x1b[32mliblodepng   compiles...\x1b[0m"
	@make -C liblodepng/ all

lode.clean:
	@make -C liblodepng/ clean

lode.fclean:
	@make -C liblodepng/ fclean

lode.re:
	@make -C liblodepng/ re

.phony: all clean fclean re
