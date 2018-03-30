/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:11:29 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/27 15:11:31 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scop.h"
#include "utils/context.h"

static void cs_init(t_cs *new_cs)
{
    new_cs->x = (t_float4){0.0f, 0.0f, 0.0f, 1.0f};
    new_cs->y = (t_float4){0.0f, 0.0f, 0.0f, 1.0f};
    new_cs->z = (t_float4){0.0f, 0.0f, 0.0f, 1.0f};
    new_cs->o = (t_float4){0.0f, 0.0f, 0.0f, 1.0f};
    new_cs->s = 1.0f;
}

static void preinit(t_sdl **sdl, t_scop_object **entry, t_scop_object **skybox)
{
    *sdl = malloc(sizeof(t_sdl));
    *entry = malloc(sizeof(t_scop_object));
    *skybox = malloc(sizeof(t_scop_object));
    ft_memset(*sdl, 0, sizeof(t_sdl));
    ft_memset(*entry, 0, sizeof(t_scop_object));
    ft_memset(*skybox, 0, sizeof(t_scop_object));
    cs_init(&((*entry)->cs));
    cs_init(&((*skybox)->cs));
}

void fit_in_view(t_stack *vertices, t_cs *cs)
{
    size_t          i;
    size_t          vert_num;
    GLfloat         max_y;
    GLfloat         min_y;
    t_vertex_ctx    *ctx;

    vert_num = stack_size(vertices);
    max_y = 0.0f;
    min_y = 0.0f;
    i = 0;
    ctx = (t_vertex_ctx*)value_at(i, vertices);
    if (!ctx)
        return ;
    max_y = (GLfloat)ctx->y;
    min_y = (GLfloat)ctx->y;
    i += 1;
    while (i < vert_num && (ctx = (t_vertex_ctx*)value_at(i, vertices)))
    {
        if ((GLfloat)ctx->y > max_y)
            max_y = (GLfloat)ctx->y;
        else if ((GLfloat)ctx->y < min_y)
            min_y = (GLfloat)ctx->y;
        ++i;
    }
    cs->o[z] -= atanf(22.5f) * (max_y - min_y);
}

int main(int ac, char *av[])
{
    t_sdl         *sdl;
    t_scop_object *entry;
    t_scop_object *skybox;
    GLuint        shader_program;

    preinit(&sdl, &entry, &skybox);
    if (ac == 2)
    {
        parse_obj(av[1], entry);
        parse_obj(SKYBOX_OBJECT_FPATH, skybox);
        fit_in_view(&entry->model.vertices, &entry->cs);

        init(sdl);
        init_skybox(skybox);

        shader_program = compile_shaders(VERT_FPATH, FRAG_FPATH);

        entry->gl.shader_program = shader_program;
        skybox->gl.shader_program = shader_program;

        load_textures();

        entry->gl.tex = texture_by_index(0);
        skybox->gl.tex = texture_by_index(2);

        load_this(entry);
        load_this(skybox);

        handle_command(sdl, entry, skybox);

        deinit(sdl);
    }
    return (0);
}
