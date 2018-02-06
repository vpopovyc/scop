/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:11:53 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/27 15:11:55 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scop.h"
#include "../parse_obj.h"
#include "utils/utils.h"

t_gl g_gl =
{
    .win = NULL
};

t_stack g_vertices = {
    .top_node = NULL,
    .bot_node = NULL
};

t_stack g_texels = {
    .top_node = NULL,
    .bot_node = NULL
};

t_stack g_normals = {
    .top_node = NULL,
    .bot_node = NULL
};

t_stack g_faces = {
    .top_node = NULL,
    .bot_node = NULL
};
