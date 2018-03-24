/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 17:43:18 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/27 17:43:40 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scop.h"
#include "../parse_obj.h"
#include "utils/utils.h"
#include <fcntl.h>

void generic_reader(char **data, float *buffer, const size_t n)
{
    register float      *buffer_iter;
    register const char **data_iter;

    data_iter = (const char **)data;
    buffer_iter = buffer;
    ft_memset(buffer, 0, n);
    while (*++data_iter) // First block is not needed
    {
        *buffer_iter = ft_atof(*data_iter);
        ++buffer_iter;
    }
    ft_ppdel(&data);
}

void read_vertices(char **data, t_stack *vertices)
{
    float buff[4];

    generic_reader(data, buff, sizeof(buff));
    enqueue(vertices, new_ctx(vertex, buff[0], buff[1], buff[2]));
}

void read_texels(char **data, t_stack *texels)
{
    float buff[2];

    generic_reader(data, buff, sizeof(buff));
    enqueue(texels, new_ctx(vertex_texture, buff[0], buff[1]));
}

void read_normal(char **data, t_stack *normals)
{
    float buff[4];

    generic_reader(data, buff, sizeof(buff));
    enqueue(normals, new_ctx(vertex_normal, buff[0], buff[1], buff[2]));
}

void process_vertex(char *line, t_model_data *scop_model)
{
    char opt_type;

    if (ft_strlen(line) > 1)
    {
        opt_type = line[1];
    }
    else
    {
        opt_type = 0;
    }
    if (opt_type == vertex_texture)
    {
        read_texels(ft_split(line, space_delim), &scop_model->texels);
    }
    else if (opt_type == vertex_normal)
    {
        read_normal(ft_split(line, space_delim), &scop_model->normals);
    }
    else
    {
        read_vertices(ft_split(line, space_delim), &scop_model->vertices);
    }
}

void process_vert_indice(char **data, t_vert_data *vert)
{
    void    *data_ptr;
    size_t  *p;

    data_ptr = (void*)data;
    p = (size_t*)vert;
    ft_memset(vert, 0, sizeof(t_vert_data));
    if (!data)
        return;
    while (*data && ((size_t)(ptrdiff_t)p - (ptrdiff_t)vert < sizeof(t_vert_data)))
    {
        *p = ft_atoi(*data);
        ++p;
        ++data;
    }
    ft_ppdel((char***)&data_ptr);
}

void process_face_indices(char *v_fst, char *v_sec, char *v_thrd, t_stack *faces)
{
    t_face_ctx  ctx;

    process_vert_indice(ft_split(v_fst, slash_delim), &ctx.vert1);
    process_vert_indice(ft_split(v_sec, slash_delim), &ctx.vert2);
    process_vert_indice(ft_split(v_thrd, slash_delim), &ctx.vert3);
    enqueue(faces, new_face_ctx(&ctx));
}

void process_face(char *line, t_stack *faces)
{
    int  i;
    char **data;

    i = 0;
    data = ft_split(line, face_delim);
    if (!data)
        return;
    while (data[0] && data[i + 1] && data[i + 2])
    {
        process_face_indices(data[0], data[i + 1], data[i + 2], faces);
        ++i;
    }
    ft_ppdel(&data);
}

void match_type(char type, char *line, t_model_data *scop_model)
{
    if (type == comment)
    {
        printf(">%s\n", line);
    }
    else if (type == object_name)
    {
        printf("> Object: %s\n", line);
    }
    else if (type == face)
    {
        process_face(line, &scop_model->faces);
    }
    else if (type == vertex)
    {
        process_vertex(line, scop_model);
    }
    else
    {
        return;
    }
}

void object_center_in(t_stack *vertices)
{
    size_t          i;
    size_t          vert_num;
    t_axis          center;
    t_vertex_ctx    *ctx;

    vert_num = stack_size(vertices);
    center = (t_axis){0.0f, 0.0f, 0.0f, 1.0f};
    i = 0;
    while (i < vert_num && (ctx = (t_vertex_ctx*)value_at(i, vertices)))
    {
        center[x_axis] += (GLfloat)ctx->x;
        center[y_axis] += (GLfloat)ctx->y;
        center[z_axis] += (GLfloat)ctx->z;
        ++i;
    }
    center = qdiv(center, vert_num);
    i = 0;
    while (i < vert_num && (ctx = (t_vertex_ctx*)value_at(i, vertices)))
    {
        ctx->x -= center[x_axis];
        ctx->y -= center[y_axis];
        ctx->z -= center[z_axis];
        ++i;
    }
}

void parse_obj(const char *file_path, t_model_data *scop_model)
{
    int     fd;
    char    *line;

    assert((fd = open(file_path, O_RDWR)) >= 0);
    while (get_next_line(fd, &line))
    {
        if (ft_is_empty(line))
            ;// Do nothing
        else
            match_type(line[0], line, scop_model);
        free(line);
    }
    object_center_in(&scop_model->vertices);
    close(fd);
}
