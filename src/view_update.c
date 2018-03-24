/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 21:15:27 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/03/24 21:15:28 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils/utils.h"

void update_axis(t_cs *cs, t_axis_type type, GLfloat delta)
{
    static GLfloat rot_x = 0.0f;
    static GLfloat rot_y = 0.0f;
    static GLfloat rot_z = 0.0f;

    if (type == x_axis)
    {
        rot_x += delta;
        cs->x = quat(1.0f, 0.0f, 0.0f, rot_x);
    }
    else if (type == y_axis)
    {
        rot_y += delta;
        cs->y = quat(0.0f, 1.0f, 0.0f, rot_y);
    }
    else
    {
        rot_z += delta;
        cs->z = quat(0.0f, 0.0f, 1.0f, rot_z);
    }
    key_pressed();
}

void update_origin(t_coord_type type, t_float4 *o, GLfloat delta)
{
    if (type == x)
        (*o)[x] += delta;
    else if (type == y)
        (*o)[y] += delta;
    else
        (*o)[z] += delta;
    key_pressed();
}

void update_scale(t_cs *cs, GLfloat delta)
{
    cs->s += (cs->s + delta > 0.0f && cs->s + delta < 1.5f) ? delta : 0.0f;
    key_pressed();
}
