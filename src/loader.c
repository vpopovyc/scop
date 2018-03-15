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

void tex_loader(t_gl *gl)
{
    unsigned int  width;
    unsigned int  height;
    int     error;
    unsigned char *png;

    width = 0;
    height = 0;
    error = lodepng_decode32_file(&png, &width, &height, "src/tex/low_polly.png");
    if (error)
    {
        printf("decoder: %s\n", lodepng_error_text(error));
        exit(-1);
    }
    glGenTextures(1, &gl->tex);
    glBindTexture(GL_TEXTURE_2D, gl->tex);
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

void append_to_vbo(t_vert_data *data, GLfloat *vbo, t_model_data *scop_model)
{
    static ssize_t offset = -1;
    t_vertex_ctx   vert;

    vert = *(t_vertex_ctx*)value_at(data->vertex - 1, &scop_model->vertices);
    vbo[++offset] = (GLfloat)vert.x;
    vbo[++offset] = (GLfloat)vert.y;
    vbo[++offset] = (GLfloat)vert.z;
    vert = *(t_vertex_ctx*)value_at(data->normal - 1, &scop_model->normals);
    vbo[++offset] = (GLfloat)vert.x;
    vbo[++offset] = (GLfloat)vert.y;
    vbo[++offset] = (GLfloat)vert.z;
    vert = *(t_vertex_ctx*)value_at(data->texture - 1, &scop_model->texels);
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

void process_vert_data(t_vert_data *data, GLfloat *vbo, GLuint *ibo, t_model_data *scop_model)
{
    static t_hash *table;
    char *key;

    if (!table){
        table = new_table(getpagesize());
    }
    key = keygen(data);
    if (key_exist(key, table))
    {
        append_to_ibo(*(GLuint*)value_of(key, table), ibo);
        // Get index in vbo from table
    }
    else
    {
        append_to_vbo(data, vbo, scop_model);
        append_to_ibo(map_index(indexgen(), key, table), ibo);
        // Add to vbo, crete new entry in hash table, get new index
    }
    free(key);
}

void add_to_buffers(t_face_ctx *ctx, GLfloat *vbo, GLuint *ibo, t_model_data *scop_model)
{
    process_vert_data(&ctx->vert1, vbo, ibo, scop_model);
    process_vert_data(&ctx->vert2, vbo, ibo, scop_model);
    process_vert_data(&ctx->vert3, vbo, ibo, scop_model);
}

void load(GLfloat *vbo, GLuint *ibo, t_model_data *scop_model)
{
    ssize_t index;
    ssize_t max_index;
    t_face_ctx  *data;

    index = 0;
    max_index = stack_size(&scop_model->faces);
    while (index < max_index)
    {
        data = (t_face_ctx*)top(&scop_model->faces);
        add_to_buffers(data, vbo, ibo, scop_model);
        pop(&scop_model->faces);
        ++index;
    }
}

void loader(t_gl *gl, t_model_data *scop_model)
{
    GLfloat *vbo_buffer;
    GLuint  *ibo_buffer;

    int     vbo_size;
    int     ibo_size;

    vbo_size = stack_size(&scop_model->faces) * sizeof(GLfloat) * 8 * 3;
    ibo_size = stack_size(&scop_model->faces) * sizeof(GLuint) * 3;

    gl->idx_num = ibo_size / sizeof(GLuint);

    vbo_buffer = malloc(vbo_size);
    ft_memset(vbo_buffer, 0, vbo_size);

    ibo_buffer = malloc(ibo_size);
    ft_memset(ibo_buffer, 0, ibo_size);

    load(vbo_buffer, ibo_buffer, scop_model);

    tex_loader(gl);

    // Gen VBO & VAO
    glGenBuffers(1, &gl->vbo);
    glGenBuffers(1, &gl->ebo);
    glGenVertexArrays(1, &gl->vao);
    // Bind VAO
    glBindVertexArray(gl->vao);
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, gl->vbo);
    glBufferData(GL_ARRAY_BUFFER, vbo_size, vbo_buffer, GL_DYNAMIC_DRAW);
    // Bind EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl->ebo);
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
