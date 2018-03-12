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

# define WINY 600
# define WINX 600
# define WINNAME "scop"

void init(void);
void deinit(void);
void parse_obj(const char *file_path);
void handle_command(void);
void loader(void);
void compile_shaders(void);

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
    // Refactor
    GLsizei         vert_num;
    GLsizei         idx_num;
    GLsizei         uv_num;
    GLsizei         norm_num;
    // ^--------------------^
    GLuint          vbo;
    GLuint          vao;
    GLuint          ebo;
    GLuint 			tex;
    // Get rid of that
    GLuint          fragment_shader;
    GLuint          vertex_shader;
    // ^--------------------^
    GLuint          shader_program;
    // Test
    t_cs            lcs;
    GLuint          quat_loc;
    t_float4        quat;
    t_float4        quat_x;
    // ^--------------------^
}                   t_gl;

extern  t_gl        g_gl;


#endif
