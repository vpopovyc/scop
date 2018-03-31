/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 18:21:40 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/02/03 18:21:41 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <context.h>
#include <stdlib.h>

void *new_hash_ctx(t_uint index)
{
    void        *ptr;

    ptr = malloc(sizeof(t_uint));
    ft_memcpy(ptr, &index, sizeof(t_uint));
    return (ptr);
}

void *new_face_ctx(t_face_ctx *ctx)
{
    void        *ptr;

    ptr = malloc(sizeof(t_face_ctx));
    ft_memcpy(ptr, ctx, sizeof(t_face_ctx));
    return (ptr);
}

void *new_ctx(t_line_type type, ...)
{
    int         i;
    int         i_max;
    double      buffer;
    void        *ptr;
    va_list     list;

    i = 0;
    i_max = type == vertex_texture ? 2 : 3;
    va_start(list, type);
    ptr = malloc(sizeof(double) * i_max);
    while (i < i_max)
    {
        buffer = va_arg(list, double);
        ptr = ft_memcpy(ptr, &buffer, sizeof(double));
        ptr = ptr + sizeof(double);
        ++i;
    }
    va_end(list);
    return (ptr - sizeof(double) * i_max);
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
