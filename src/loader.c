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

ssize_t *indexgen(void)
{
    static ssize_t index = -1;

    ++index;
    return (&index);
}

ssize_t *offset_of(t_buffer_type type)
{
    static ssize_t vbo_offset = 0;
    static ssize_t ibo_offset = 0;

    if (type == e_vbo)
        return (&vbo_offset);
    else if (type == e_ibo)
        return (&ibo_offset);
    else
        return (NULL);
}

void append_to_ibo(GLuint index, GLuint *ibo)
{
    ssize_t *offset;

    offset = offset_of(e_ibo);
    ibo[*offset] = index;
    ++*offset;
}

void append_to_vbo(t_vert_data *data, GLfloat *vbo, t_model_data *scop_model)
{
    ssize_t *offset;
    static t_vertex_ctx fallback = (t_vertex_ctx){0.0f, 0.0f, 0.0f};
    void            *value;
    t_vertex_ctx    vert;

    offset = offset_of(e_vbo);
    value = value_at(data->vertex - 1, &scop_model->vertices);
    vert = value ? *(t_vertex_ctx*)value : fallback;
    vbo[*offset] = (GLfloat)vert.x;
    vbo[++*offset] = (GLfloat)vert.y;
    vbo[++*offset] = (GLfloat)vert.z;
    value = value_at(data->normal - 1, &scop_model->normals);
    vert = (value ? *(t_vertex_ctx*)value : fallback);
    vbo[++*offset] = (GLfloat)vert.x;
    vbo[++*offset] = (GLfloat)vert.y;
    vbo[++*offset] = (GLfloat)vert.z;
    value = value_at(data->texture - 1, &scop_model->texels);
    vert = value ? *(t_vertex_ctx*)value : fallback;
    vbo[++*offset] = (GLfloat)vert.x;
    vbo[++*offset] = (GLfloat)vert.y;
    ++*offset;
}

ssize_t map_index(ssize_t index, char *key, t_hash *table)
{
    insert(key, new_hash_ctx(index), table);
    return (index);
}

t_hash *table_instance(t_hash *ptr)
{
    static t_hash *stored_ptr;

    if (ptr)
        stored_ptr = ptr;
    return (stored_ptr);
}

void process_vert_data(t_vert_data *data, GLfloat *vbo, GLuint *ibo, t_model_data *scop_model)
{
    t_hash *table;
    char *key;

    table = table_instance(NULL);
    key = keygen(data);
    if (key_exist(key, table))
    {
        append_to_ibo(*(GLuint*)value_of(key, table), ibo);
        // Get index in vbo from table
    }
    else
    {
        append_to_vbo(data, vbo, scop_model);
        append_to_ibo(map_index(*indexgen(), key, table), ibo);
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
    t_hash      *table;

    index = 0;
    max_index = stack_size(&scop_model->faces);
    table = new_table(getpagesize());
    table_instance(table);
    *indexgen() = -1;
    *offset_of(e_vbo) = 0;
    *offset_of(e_ibo) = 0;
    while (index < max_index)
    {
        data = (t_face_ctx*)top(&scop_model->faces);
        add_to_buffers(data, vbo, ibo, scop_model);
        pop(&scop_model->faces);
        ++index;
    }
    free((void*)table - sizeof(int));
}

void load_this(t_scop_object *entry)
{
    GLfloat *vbo_buffer;
    GLuint  *ibo_buffer;

    int     vbo_size;
    int     ibo_size;

    vbo_size = stack_size(&entry->model.faces) * sizeof(GLfloat) * 8 * 3;
    ibo_size = stack_size(&entry->model.faces) * sizeof(GLuint) * 3;

    entry->gl.idx_num = ibo_size / sizeof(GLuint);

    vbo_buffer = malloc(vbo_size);
    ft_memset(vbo_buffer, 0, vbo_size);

    ibo_buffer = malloc(ibo_size);
    ft_memset(ibo_buffer, 0, ibo_size);

    load(vbo_buffer, ibo_buffer, &entry->model);

    // Gen VBO & VAO
    glGenBuffers(1, &entry->gl.vbo);
    glGenBuffers(1, &entry->gl.ibo);
    glGenVertexArrays(1, &entry->gl.vao);
    // Bind VAO
    glBindVertexArray(entry->gl.vao);
    // Turn on all attribs
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, entry->gl.vbo);
    glBufferData(GL_ARRAY_BUFFER, vbo_size, vbo_buffer, GL_DYNAMIC_DRAW);
    // Bind IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entry->gl.ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibo_size, ibo_buffer, GL_DYNAMIC_DRAW);
    // Attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));

    glBindVertexArray(0);
    free(vbo_buffer);
    free(ibo_buffer);
}
