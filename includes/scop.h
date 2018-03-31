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

# define WINY       800
# define WINX       800
# define WINNAME    "scop"
# define TSENS      (0.009f)
# define RSENS      (1.0f)
# define SSENS      (0.2f)
# define TEXTNUM    (4)
# define VERT_FPATH ("src/shaders/vertex.glsl")
# define FRAG_FPATH ("src/shaders/fragment.glsl")
# define SKYBOX_OBJECT_FPATH ("src/tex/skybox.obj")

typedef enum        e_axis_type
{
    x_axis,
    y_axis,
    z_axis
}                   t_axis_type;

typedef enum        e_coord_type
{
    x,
    y,
    z
}                   t_coord_type;

typedef enum        e_buffer_type
{
    e_vbo,
    e_ibo
}                   t_buffer_type;

typedef struct      s_sdl
{
    SDL_Window      *win;
    SDL_GLContext   ctx;
    SDL_Event       event;
    _Bool           feedback;
}                   t_sdl;

typedef struct      s_gl
{
    GLuint          vao;
    GLuint          vbo;
    GLuint          ibo;
    GLuint          tex;
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

typedef struct      s_cs
{
    t_axis          x;
    t_axis          y;
    t_axis          z;
    t_float4        o;
    GLfloat         s;
}                   t_cs;

typedef struct      s_scop_object
{
    t_gl            gl;
    t_cs            cs;
    t_model_data    model;
}                   t_scop_object;

void init(t_sdl *sdl);
void deinit(t_sdl *sdl);
void parse_obj(const char *file_path, t_scop_object *entry);
void init_skybox(t_scop_object *skybox);
GLuint compile_shaders(const char *vert_fpath, const char *frag_fpath);
void load_this(t_scop_object *entry);
GLuint texture_by_index(int i);
void load_textures(void);

void handle_command(t_sdl *sdl, t_scop_object *entry, t_scop_object *skybox);

void draw(t_sdl *sdl, t_scop_object *entry, t_scop_object *skybox);

#endif
