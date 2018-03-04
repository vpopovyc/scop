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


void    object_center_in(t_axis center, GLfloat *buffer, size_t size)
{
    size_t  i;
    size_t  j;
    float   tmp;

    i = 0;
    j = 0;
    while (i < size)
    {
        tmp = buffer[i + j];
        buffer[i + j] = tmp - center[0];
        tmp = buffer[i + ++j];
        buffer[i + j] = tmp - center[1];
        tmp = buffer[i + ++j];
        buffer[i + j] = tmp - center[2];
        ++i;
    }
}

void get_vertices(GLfloat *buffer, const size_t size)
{
    size_t          i;
    size_t          j;
    t_vertex_ctx    *ctx;
    t_axis          center;

    i = 0;
    j = 0;
    center = (t_axis){0.0f, 0.0f, 0.0f, 1.0f};
    while (i < size)
    {
        ctx = (t_vertex_ctx*)top(&g_vertices);
        buffer[i + j] = (GLfloat)ctx->x;
        center[0] += buffer[i + j];
        buffer[i + ++j] = (GLfloat)ctx->y;
        center[1] += buffer[i + j];
        buffer[i + ++j] = (GLfloat)ctx->z;
        center[2] += buffer[i + j];
        pop(&g_vertices);
        ++i;
    }
    center = qdiv(center, size);
    object_center_in(center, buffer, size);
}

void get_uvs(GLfloat *buffer, size_t size, const size_t offset)
{
    size_t          i;
    size_t          j;
    t_vertex_ctx    *ctx;

    i = offset;
    j = 0;
    size += offset;
    while (i < size)
    {
        ctx = (t_vertex_ctx*)top(&g_texels);
        buffer[i + j] = (GLfloat)ctx->x;
        buffer[i + ++j] = (GLfloat)ctx->y;
        pop(&g_texels);
        ++i;
    }
}

void get_normals(GLfloat *buffer, size_t size, const size_t offset)
{
    size_t          i;
    size_t          j;
    t_vertex_ctx    *ctx;

    i = offset;
    j = 0;
    size += offset;
    while (i < size)
    {
        ctx = (t_vertex_ctx*)top(&g_normals);
        buffer[i + j] = (GLfloat)ctx->x;
        buffer[i + ++j] = (GLfloat)ctx->y;
        buffer[i + ++j] = (GLfloat)ctx->z;
        pop(&g_normals);
        ++i;
    }
}

GLfloat *get_vbo(size_t vbo_size)
{
    GLfloat         *buffer;

    buffer = malloc(vbo_size);
    get_vertices(buffer, g_gl.vert_num / 3);
    get_uvs(buffer, g_gl.uv_num / 2, g_gl.vert_num);
    get_normals(buffer, g_gl.norm_num / 3, g_gl.vert_num + g_gl.uv_num);
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
        buffer[i + ++j] = (GLuint)ctx->vert2.vertex;
        printf("face index in:%lu value: %u\n", i + j, buffer[i + j]);
        buffer[i + ++j] = (GLuint)ctx->vert3.vertex;
        printf("face index in:%lu value: %u\n", i + j, buffer[i + j]);
        // Next iter
        pop(&g_faces);
        ++i;
    }
    printf("EBO stack size: %d\n", stack_size(&g_faces));
    return (buffer);
}

void tex_loader(void)
{
    unsigned int  width;
    unsigned int  height;
    int     error;
    unsigned char *png;

    width = 0;
    height = 0;
    error = lodepng_decode32_file(&png, &width, &height, "src/tex/uv.png");
    if (error)
    {
        printf("decoder: %s\n", lodepng_error_text(error));

        exit(-1);
    }
    glGenTextures(1, &g_gl.tex);
    glBindTexture(GL_TEXTURE_2D, g_gl.tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, png);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    free(png);
}

void loader(void)
{
    GLfloat *vbo_buffer;
    GLuint  *ebo_buffer;

    g_gl.uv_num = stack_size(&g_texels) * 2;
    g_gl.norm_num = stack_size(&g_normals) * 3;
    g_gl.vert_num = stack_size(&g_vertices) * 3;
    g_gl.idx_num = stack_size(&g_faces) * 3;
    vbo_buffer = get_vbo((g_gl.vert_num + g_gl.uv_num + g_gl.norm_num) * sizeof(GLfloat));
    ebo_buffer = get_indices(g_gl.idx_num * sizeof(GLuint));

    tex_loader();

    // Gen VBO & VAO
    glGenBuffers(1, &g_gl.vbo);
    glGenBuffers(1, &g_gl.ebo);
    glGenVertexArrays(1, &g_gl.vao);
    // Bind VAO
    glBindVertexArray(g_gl.vao);
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, g_gl.vbo);
    glBufferData(GL_ARRAY_BUFFER, (g_gl.vert_num + g_gl.uv_num + g_gl.norm_num) * sizeof(GLfloat), vbo_buffer, GL_DYNAMIC_DRAW);
    // Bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_gl.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, g_gl.idx_num * sizeof(GLuint), ebo_buffer, GL_DYNAMIC_DRAW);
    // Attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 2 * sizeof(GLfloat), (GLvoid*)(g_gl.vert_num * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 3 * sizeof(GLfloat), (GLvoid*)((g_gl.vert_num + g_gl.uv_num) * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    free(vbo_buffer);
}
