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

void process_mtl_lib(void)
{
    // TODO: Investigate about that feature
    perror("Not implemented");
}

int space_delim(int c)
{
    if (c == ' ')
        return (1);
    else
        return (0);
}

int face_delim(int c)
{
    if (c == 'f' || c == ' ')
        return (1);
    else
        return (0);
}

int slash_delim(int c)
{
    if (c == '/')
        return (1);
    else
        return (0);
}

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

void read_vertices(char **data)
{
    float buff[4];

    generic_reader(data, buff, sizeof(buff));
    enqueue(&g_vertices, new_ctx(vertex, buff[0], buff[1], buff[2]));
}

void read_texels(char **data)
{
    float buff[2];

    generic_reader(data, buff, sizeof(buff));
    enqueue(&g_texels, new_ctx(vertex_texture, buff[0], buff[1]));
}

void read_normal(char **data)
{
    float buff[4];

    generic_reader(data, buff, sizeof(buff));
    enqueue(&g_normals, new_ctx(vertex_normal, buff[0], buff[1], buff[2]));
}

void process_vertex(char *line)
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
        read_texels(ft_split(line, space_delim));
    }
    else if (opt_type == vertex_normal)
    {
        read_normal(ft_split(line, space_delim));
    }
    else if (opt_type == uv_mapping)
    {
        // TODO: Process uv's
    }
    else
    {
        read_vertices(ft_split(line, space_delim));
    }
}

void process_vert_indice(char **data, t_vert_data *vert)
{
    void    *data_ptr;
    size_t  *p;

    data_ptr = (void*)data;
    p = (size_t*)vert;
    ft_memset(vert, 0, sizeof(t_vert_data));
    // TODo: Unsafe ptr reference
    while (*data)
    {
        *p = ft_atoi(*data);
        ++p;
        ++data;
    }
    ft_ppdel((char***)&data_ptr);
}

void process_face_indices(char *v_fst, char *v_sec, char *v_thrd)
{
    t_face_ctx  ctx;

    process_vert_indice(ft_split(v_fst, slash_delim), &ctx.vert1);
    process_vert_indice(ft_split(v_sec, slash_delim), &ctx.vert2);
    process_vert_indice(ft_split(v_thrd, slash_delim), &ctx.vert3);
    enqueue(&g_faces, new_face_ctx(&ctx));
}

void process_face(char *line)
{
    int  i;
    char **data;

    i = 0;
    data = ft_split(line, face_delim);
    while (data[i + 2])
    {
        process_face_indices(data[0], data[i + 1], data[i + 2]);
        ++i;
    }
    ft_ppdel(&data);
}

void match_type(char type, char *line)
{
    if (type == comment)
    {
        printf(">%s\n", line);
    }
    else if (type == object_name)
    {
        printf("> Object: %s\n", line);
    }
    else if (type == mtllib)
    {
        // TODO: Process mtl
        process_mtl_lib();
    }
    else if (type == face)
    {
        process_face(line);
    }
    else if (type == vertex)
    {
        process_vertex(line);
    }
    else
    {
        // TODO: Think about that case
        perror("Unexpected type, skipping it\n");
    }
}

void parse_obj(const char *file_path)
{
    int     fd;
    char    *line;

    assert((fd = open(file_path, O_RDWR)) >= 0);
    while (get_next_line(fd, &line))
    {
        if (ft_is_empty(line))
            ;// Do nothing
        else
            match_type(line[0], line);
        free(line);
    }
    close(fd);
}
