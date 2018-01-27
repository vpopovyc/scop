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

static inline void __exit(int excode)
{
    deinit();
    exit(excode);
}

void handle_command(void)
{
    uint8_t *keystate;
    
    while (1)
    {
        keystate = (unsigned char *)SDL_GetKeyboardState(NULL);
        SDL_PollEvent(&g_gl.event);
        if ((g_gl.event.type == SDL_QUIT) || keystate[SDL_SCANCODE_ESCAPE])
            __exit(0);
    }
}
