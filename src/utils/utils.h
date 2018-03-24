/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:12:12 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/27 15:12:13 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __UTILS_H
# define __UTILS_H

# include "context.h"
# include <libft.h>
# include "../../scop.h"

int space_delim(int c);
int face_delim(int c);
int slash_delim(int c);

void update_axis(t_cs *cs, t_axis_type type, GLfloat delta);
void update_origin(t_coord_type type, t_float4 *o, GLfloat delta);
void update_scale(t_cs *cs, GLfloat delta);

#endif
