/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 12:55:15 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/03/25 12:55:17 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scop.h"
#include "utils/context.h"

static void scale(t_stack *vertices, GLfloat scale)
{
    size_t          i;
    size_t          vert_num;
    t_vertex_ctx    *ctx;

    i = 0;
    vert_num = stack_size(vertices);
    while (i < vert_num && (ctx = (t_vertex_ctx*)value_at(i, vertices)))
    {
        ctx->x *= scale;
        ctx->y *= scale;
        ctx->z *= scale;
        ++i;
    }
}

void init_skybox(t_scop_object *skybox)
{
    scale(&skybox->model.vertices, 90.0f);
}

