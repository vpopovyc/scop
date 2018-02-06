/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:12:12 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/27 15:12:13 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __SCOP_H
# define __SCOP_H

# include <OpenGL/gl.h>
# include <SDL2/SDL.h>
# include <libft/libft.h>

# include <assert.h>
# include <stdlib.h>
# include <stdio.h>

# define WINY 600
# define WINX 600
# define WINNAME "scop"

void init(void);
void deinit(void);
void parse_obj(const char *file_path);
void handle_command(void);
void load_vertices_to_VBO(void);

typedef struct      s_gl
{
    SDL_Window      *win;
    SDL_GLContext   ctx;
    SDL_Event       event;
    GLuint          v_vbo;
    GLuint          vao;
}                   t_gl;

extern  t_gl        g_gl;


#endif
