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

#define GL3_PROTOTYPES 1
#include <GL/glew.h>
#include <SDL2/SDL.h>

# include <libft.h>
# include <lodepng.h> 
# include <assert.h>
# include <stdlib.h>
# include <stdio.h>

# define WINY 800
# define WINX 800
# define WINNAME "scop"

typedef struct      s_cs
{
    t_axis          x;
    t_axis          y;
    t_axis          z;
}                   t_cs;

typedef enum        e_axis_type
{
    x_axis,
    y_axis,
    z_axis
}                   t_axis_type;

typedef struct      s_gl
{
    SDL_Window      *win;
    SDL_GLContext   ctx;
    SDL_Event       event;
    GLuint          vbo;
    GLuint          vao;
    GLuint          tex;
    GLuint          ebo;
    GLsizei         idx_num;
    GLuint          shader_program;
}                   t_gl;

typedef struct      s_model_data
{
    t_stack         vertices;
    t_stack         texels;
    t_stack         normals;
    t_stack         faces;
}                   t_model_data;

void init(t_gl *gl);
void deinit(t_gl *gl);
void parse_obj(const char *file_path, t_model_data *scop_model);
void handle_command(t_gl *gl);
void loader(t_gl *gl, t_model_data *scop_model);
void compile_shaders(t_gl *gl);

#endif
