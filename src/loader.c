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

GLfloat *get_vertices(size_t vbo_size)
{
    GLfloat         *buffer;
    size_t          i;
    size_t          j;
    size_t          size;
    t_vertex_ctx    *ctx;

    i = 0;
    j = 0;
    size = g_gl.vert_num / 3;
    buffer = malloc(vbo_size);
    while (i < size)
    {
        ctx = (t_vertex_ctx*)top(&g_vertices);
        buffer[i + j] = (GLfloat)ctx->x;
        printf("index in:%lu value: %f\n", i + j, buffer[i + j]);
        buffer[i + ++j] = (GLfloat)ctx->y;
        printf("index in:%lu value: %f\n", i + j, buffer[i + j]);
        buffer[i + ++j] = (GLfloat)ctx->z;
        printf("index in:%lu value: %f\n", i + j, buffer[i + j]);
        pop(&g_vertices);
        ++i;
    }
    printf("VBO stack size: %d\n", stack_size(&g_vertices));
    return (buffer);
}

GLuint  *get_indices(size_t ebo_size)
{
    GLuint      *buffer;
    size_t      i;
    size_t      j;
    size_t      size;
    t_face_ctx  *ctx;

    i = 0;
    j = 0;
    size = g_gl.idx_num / 3;
    buffer = malloc(ebo_size);
    while (i < size)
    {
        // Unwrap 
        ctx = (t_face_ctx*)top(&g_faces);
        buffer[i + j] = (GLuint)ctx->vert1.vertex - 1;
        printf("face index in:%lu value: %u\n", i + j, buffer[i + j]);
        buffer[i + ++j] = (GLuint)ctx->vert2.vertex - 1;
        printf("face index in:%lu value: %u\n", i + j, buffer[i + j]);
        buffer[i + ++j] = (GLuint)ctx->vert3.vertex - 1;
        printf("face index in:%lu value: %u\n", i + j, buffer[i + j]);
        // Next iter
        pop(&g_faces);
        ++i;
    }
    printf("EBO stack size: %d\n", stack_size(&g_faces));
    return (buffer);
}

void loader(void)
{
    GLfloat *vbo_buffer;
    GLuint  *ebo_buffer;

    
    g_gl.vert_num = stack_size(&g_vertices) * 3;
    g_gl.idx_num = stack_size(&g_faces) * 3;
    vbo_buffer = get_vertices(g_gl.vert_num * sizeof(GLfloat));
    ebo_buffer = get_indices(g_gl.idx_num * sizeof(GLuint));
    // Gen VBO & VAO
    glGenBuffers(1, &g_gl.vbo);
    glGenBuffers(1, &g_gl.ebo);
    glGenVertexArrays(1, &g_gl.vao);
    // Bind VAO
    glBindVertexArray(g_gl.vao);
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, g_gl.vbo);
    glBufferData(GL_ARRAY_BUFFER, g_gl.vert_num * sizeof(GLfloat), vbo_buffer, GL_DYNAMIC_DRAW);
    // Bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_gl.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_gl.idx_num * sizeof(GLuint), ebo_buffer, GL_DYNAMIC_DRAW);
    // Attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    free(vbo_buffer);
}
