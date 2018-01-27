/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 19:14:01 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/27 19:14:02 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __PARSE_OBJ_H
# define __PARSE_OBJ_H

typedef enum    e_line_type
{
    comment = '#',
    mtllib = 'm',
    object_name = 'o',
    group_name = 'g',
    face = 'f',
    vertex = 'v',
    vertex_texture = 't',
    vertex_normal = 'n',
    uv_mapping = 'p'
}               t_line_type;

#endif
