/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:11:44 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/27 15:11:45 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scop.h"
# include "utils/utils.h"

void scale(t_cs *cs, SDL_Event *event)
{
    if (event->wheel.y == 1)
        update_scale(cs, SSENS);
    if (event->wheel.y == -1)
        update_scale(cs, -SSENS);
}

void rotate(t_cs *cs, uint8_t *keystate)
{
    if (keystate[SDL_SCANCODE_H])
        update_axis(cs, y_axis, RSENS);
    if (keystate[SDL_SCANCODE_L])
        update_axis(cs, y_axis, -RSENS);
    if (keystate[SDL_SCANCODE_J])
        update_axis(cs, x_axis, RSENS);
    if (keystate[SDL_SCANCODE_K])
        update_axis(cs, x_axis, -RSENS);
    if (keystate[SDL_SCANCODE_U])
        update_axis(cs, z_axis, RSENS);
    if (keystate[SDL_SCANCODE_I])
        update_axis(cs, z_axis, -RSENS);
}

void translate(t_cs *cs, uint8_t *keystate)
{
    if (keystate[SDL_SCANCODE_X])
        update_origin(x, &cs->o, TSENS);
    if (keystate[SDL_SCANCODE_Z])
        update_origin(x, &cs->o, -TSENS);
    if (keystate[SDL_SCANCODE_V])
        update_origin(y, &cs->o, TSENS);
    if (keystate[SDL_SCANCODE_C])
        update_origin(y, &cs->o, -TSENS);
    if (keystate[SDL_SCANCODE_N])
        update_origin(z, &cs->o, TSENS);
    if (keystate[SDL_SCANCODE_B])
        update_origin(z, &cs->o, -TSENS);
}

void cs_init(t_cs *new_cs)
{
    new_cs->x = (t_float4){0.0f, 0.0f, 0.0f, 1.0f};
    new_cs->y = (t_float4){0.0f, 0.0f, 0.0f, 1.0f};
    new_cs->z = (t_float4){0.0f, 0.0f, 0.0f, 1.0f};
    new_cs->o = (t_float4){0.0f, 0.0f, 0.0f, 1.0f};
    new_cs->s = 1.0f;
}

void handle_command(t_gl *gl)
{
    uint8_t *keystate;
    t_cs    object_cs;

    cs_init(&object_cs);
    draw(gl, &object_cs);
    while (1)
    {
        keystate = (unsigned char *)SDL_GetKeyboardState(NULL);
        SDL_PollEvent(&gl->event);
        if ((gl->event.type == SDL_QUIT) || keystate[SDL_SCANCODE_ESCAPE])
            return ;
        scale(&object_cs, &gl->event);
        rotate(&object_cs, keystate);
        translate(&object_cs, keystate);
        if (is_key_pressed())
            draw(gl, &object_cs);
    }
}
