/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 23:30:45 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/02/06 23:30:46 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scop.h"
#include "utils/utils.h"

GLfloat *get_vertices()
{
    GLfloat         *buffer;
    size_t          i;
    size_t          size;
    t_vertex_ctx    *ctx;

    i = 0;
    size = stack_size(&g_vertices);
    buffer = malloc(sizeof(GLfloat) * 3 * size);
    while (i < size)
    {
        ctx = (t_vertex_ctx*)top(&g_vertices);
        buffer[i] = (GLfloat)ctx->x;
        buffer[i + 1] = (GLfloat)ctx->y;
        buffer[i + 2] = (GLfloat)ctx->z;
        pop(&g_vertices);
        ++i;
    }
    printf("left over stack size: %d\n", stack_size(&g_vertices));
    return (buffer);
}

void load_vertices_to_VBO(void)
{
    GLfloat *vert_buffer;
    // TODO: Think about binding VAO
    vert_buffer = get_vertices();
    glGenBuffers(1, &g_gl.v_vbo);
    // TODO: Copy vertex data to vbo
}
