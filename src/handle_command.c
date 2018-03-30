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

void rotate(t_cs *cs, uint8_t *keystate, _Bool orbit_camera_switch)
{
    if (keystate[SDL_SCANCODE_H] || orbit_camera_switch)
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

void texture_change(t_scop_object *entry, t_scop_object *skybox, uint8_t *keystate)
{
    static int object_tex_index;
    static int skybox_tex_index;

    if (keystate[SDL_SCANCODE_Q])
    {
        entry->gl.tex = texture_by_index(++object_tex_index % 2);
        key_pressed();
        SDL_Delay(200);
    }
    if (keystate[SDL_SCANCODE_E])
    {
        skybox->gl.tex = texture_by_index((++skybox_tex_index % 2) + 2);
        key_pressed();
        SDL_Delay(200);
    }
}

void handle_command(t_sdl *sdl, t_scop_object *entry, t_scop_object *skybox)
{
    uint8_t *keystate;
    _Bool   orbit_camera_switch;

    orbit_camera_switch = 1;
    draw(sdl, entry, skybox);
    while (1)
    {
        keystate = (unsigned char *)SDL_GetKeyboardState(NULL);
        SDL_PollEvent(&(sdl->event));
        if ((sdl->event.type == SDL_QUIT) || keystate[SDL_SCANCODE_ESCAPE])
            return ;
        if (keystate[SDL_SCANCODE_F])
        {
            sdl->feedback ^= 1;
            SDL_Delay(200);
        }
        if (keystate[SDL_SCANCODE_W])
        {
            orbit_camera_switch ^= 1;
            SDL_Delay(200);
        }
        scale(&entry->cs, &sdl->event);
        if (!sdl->feedback)
            rotate(&entry->cs, keystate, orbit_camera_switch);
        if (sdl->feedback && !orbit_camera_switch)
            rotate(&skybox->cs, keystate, orbit_camera_switch);
        if (!sdl->feedback)
            translate(&entry->cs, keystate);
        texture_change(entry, skybox, keystate);
        if (is_key_pressed()) {
            draw(sdl, entry, skybox);
        }

    }
}
