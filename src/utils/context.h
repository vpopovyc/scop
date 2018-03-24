/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 18:21:34 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/02/03 18:21:35 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CONTEXT_H
# define __CONTEXT_H

# include <stdarg.h>
# include <stddef.h>
# include <libft.h>
# include "../../parse_obj.h"

typedef struct s_face_ctx t_face_ctx;
typedef struct s_vert_data t_vert_data;

void *new_ctx(t_line_type type, ...) __attribute__ ((malloc));

void *new_face_ctx(t_face_ctx *ctx) __attribute__ ((malloc));

void *new_hash_ctx(t_uint index) __attribute__ ((malloc));

char *keygen(t_vert_data *data);

typedef struct  s_vert_data
{
    size_t      vertex;
    size_t      texture;
    size_t      normal;
}               t_vert_data;

typedef struct  s_vertex_ctx
{
    double      x;
    double      y;
    double      z;
}               t_vertex_ctx;

typedef struct  s_face_ctx
{
    t_vert_data vert1;
    t_vert_data vert2;
    t_vert_data vert3;
}               t_face_ctx;

#endif
