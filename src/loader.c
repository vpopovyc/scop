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


// void    object_center_in(t_axis center, GLfloat *buffer, size_t size)
// {
//     size_t  i;
//     size_t  j;
//     float   tmp;

//     i = 0;
//     j = 0;
//     while (i < size)
//     {
//         tmp = buffer[i + j];
//         buffer[i + j] = tmp - center[0];
//         tmp = buffer[i + ++j];
//         buffer[i + j] = tmp - center[1];
//         tmp = buffer[i + ++j];
//         buffer[i + j] = tmp - center[2];
//         ++i;
//     }
// }

// void get_vertices(GLfloat *buffer, const size_t size)
// {
//     size_t          i;
//     size_t          j;
//     t_vertex_ctx    *ctx;
//     t_axis          center;

//     i = 0;
//     j = 0;
//     center = (t_axis){0.0f, 0.0f, 0.0f, 1.0f};
//     while (i < size)
//     {
//         ctx = (t_vertex_ctx*)top(&g_vertices);
//         buffer[i + j] = (GLfloat)ctx->x;
//         center[0] += buffer[i + j];
//         buffer[i + ++j] = (GLfloat)ctx->y;
//         center[1] += buffer[i + j];
//         buffer[i + ++j] = (GLfloat)ctx->z;
//         center[2] += buffer[i + j];
//         pop(&g_vertices);
//         ++i;
//     }
//     center = qdiv(center, size);
//     object_center_in(center, buffer, size);
// }

// GLfloat *get_vbo(size_t vbo_size)
// {
//     GLfloat         *buffer;

//     buffer = malloc(vbo_size);
//     get_vertices(buffer, g_gl.vert_num / 3);
//     get_uvs(buffer, g_gl.uv_num / 2, g_gl.vert_num);
//     get_normals(buffer, g_gl.norm_num / 3, g_gl.vert_num + g_gl.uv_num);
//     return (buffer);
// }

// GLuint  *get_indices(size_t ebo_size)
// {
//     GLuint      *buffer;
//     size_t      i;
//     size_t      j;
//     size_t      size;
//     t_face_ctx  *ctx;

//     i = 0;
//     j = 0;
//     size = g_gl.idx_num / 3;
//     buffer = malloc(ebo_size);
//     while (i < size)
//     {
//         // Unwrap 
//         ctx = (t_face_ctx*)top(&g_faces);
//         buffer[i + j] = (GLuint)ctx->vert1.vertex - 1;
//         printf("face index in:%lu value: %u\n", i + j, buffer[i + j]);
//         buffer[i + ++j] = (GLuint)ctx->vert2.vertex - 1;
//         printf("face index in:%lu value: %u\n", i + j, buffer[i + j]);
//         buffer[i + ++j] = (GLuint)ctx->vert3.vertex - 1;
//         printf("face index in:%lu value: %u\n", i + j, buffer[i + j]);
//         // Next iter
//         pop(&g_faces);
//         ++i;
//     }
//     printf("EBO stack size: %d\n", stack_size(&g_faces));
//     return (buffer);
// }

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

char *keygen(t_vert_data *data)
{
    char *v_str;
    char *n_str;
    char *t_str;
    char *res;
    char *tmp;

    tmp = ft_itoa(data->vertex, 10);
    v_str = ft_strjoin(tmp, "/");
    free(tmp);
    tmp = ft_itoa(data->normal, 10);
    n_str = ft_strjoin(tmp, "/");
    free(tmp);
    t_str = ft_itoa(data->texture, 10);
    tmp = ft_strjoin(v_str, n_str);
    res = ft_strjoin(tmp, t_str);
    free(tmp);
    free(v_str);
    free(n_str);
    free(t_str);
    return (res);
}

ssize_t indexgen(void)
{
    static ssize_t index = -1;

    return (++index);
}

void append_to_vbo(t_vert_data *data, GLfloat *vbo)
{
    static ssize_t offset = -1;
    t_vertex_ctx   vert;

    vert = *(t_vertex_ctx*)value_at(data->vertex - 1, &g_vertices);
    vbo[++offset] = (GLfloat)vert.x;
    vbo[++offset] = (GLfloat)vert.y;
    vbo[++offset] = (GLfloat)vert.z;
    vert = *(t_vertex_ctx*)value_at(data->normal - 1, &g_normals);
    vbo[++offset] = (GLfloat)vert.x;
    vbo[++offset] = (GLfloat)vert.y;
    vbo[++offset] = (GLfloat)vert.z;
    vert = *(t_vertex_ctx*)value_at(data->texture - 1, &g_texels);
    vbo[++offset] = (GLfloat)vert.x;
    vbo[++offset] = (GLfloat)vert.y;
}

void append_to_ibo(GLuint index, GLuint *ibo)
{
    static ssize_t offset = 0;

    ibo[offset] = index;
    ++offset;
}

ssize_t map_index(ssize_t index, char *key, t_hash *table)
{
    insert(key, new_hash_ctx(index), table);
    return (index);
}

void process_vert_data(t_vert_data *data, GLfloat *vbo, GLuint *ibo)
{
    static t_hash *table;
    char *key;

    if (!table){
        table = new_table(getpagesize());
        printf("pzdec %p\n", table);
    }
    key = keygen(data);
    if (key_exist(key, table))
    {
        append_to_ibo(*(GLuint*)value_of(key, table), ibo);
        // Get index in vbo from table
    }
    else
    {
        append_to_vbo(data, vbo);
        append_to_ibo(map_index(indexgen(), key, table), ibo);
        // Add to vbo, crete new entry in hash table, get new index
    }
    free(key);
}

void add_to_buffers(t_face_ctx *ctx, GLfloat *vbo, GLuint *ibo)
{
    process_vert_data(&ctx->vert1, vbo, ibo);
    printf("process_vert_data(&ctx->vert1, vbo, ibo)\n");
    process_vert_data(&ctx->vert2, vbo, ibo);
    printf("process_vert_data(&ctx->vert2, vbo, ibo)\n");
    process_vert_data(&ctx->vert3, vbo, ibo);
    printf("process_vert_data(&ctx->vert3, vbo, ibo)\n");
}

void load(GLfloat *vbo, GLuint *ibo)
{
    ssize_t index;
    ssize_t max_index;
    t_face_ctx  *data;

    index = 0;
    max_index = stack_size(&g_faces);
    while (index < max_index)
    {
        data = (t_face_ctx*)top(&g_faces);
        add_to_buffers(data, vbo, ibo);
        pop(&g_faces);
        ++index;
    }
}

void loader(void)
{
    GLfloat *vbo_buffer;
    GLuint  *ibo_buffer;

    int     vbo_size;
    int     ibo_size;

    vbo_size = stack_size(&g_faces) * sizeof(GLfloat) * 8 * 3;
    ibo_size = stack_size(&g_faces) * sizeof(GLuint) * 3;

    g_gl.idx_num = ibo_size / sizeof(GLuint);

    printf("idx_num %u\n", g_gl.idx_num);

    vbo_buffer = malloc(vbo_size);
    ft_memset(vbo_buffer, vbo_size, 0);

    ibo_buffer = malloc(ibo_size);
    ft_memset(ibo_buffer, ibo_size, 0);

    printf("pos stack size %d\n", stack_size(&g_vertices));
    printf("norm stack size %d\n", stack_size(&g_normals));
    printf("tex stack size %d\n", stack_size(&g_texels));

    load(vbo_buffer, ibo_buffer);

    for (int i = 0; i < g_gl.idx_num; i++)
    {
        printf("index in buffer: %u\n", ibo_buffer[i]);
    }

    printf("vbo_size: %lu\n", vbo_size / sizeof(GLfloat) / 8);

    for (t_uint i = 0; i < vbo_size / sizeof(GLfloat) / 8;)
    {
        printf("\n-----------\nvertex: \nposition: {\n\t x: %f  y: %f z: %f\n}\nnormals: {\n\t x: %f y:%f z:%f\n}\ntextures: {\n\t x: %f y: %f\n}\n", 
                                        vbo_buffer[i], vbo_buffer[i + 1], vbo_buffer[i + 2], vbo_buffer[i + 3], vbo_buffer[i + 4], vbo_buffer[i + 5], vbo_buffer[i + 6], vbo_buffer[i + 7]);
        i += 8;
    }

    tex_loader();

    // Gen VBO & VAO
    glGenBuffers(1, &g_gl.vbo);
    glGenBuffers(1, &g_gl.ebo);
    glGenVertexArrays(1, &g_gl.vao);
    // Bind VAO
    glBindVertexArray(g_gl.vao);
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, g_gl.vbo);
    glBufferData(GL_ARRAY_BUFFER, vbo_size, vbo_buffer, GL_DYNAMIC_DRAW);
    // Bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_gl.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibo_size, ibo_buffer, GL_DYNAMIC_DRAW);
    // Attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1); 
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    free(vbo_buffer);
}
