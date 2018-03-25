/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_gl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:22:45 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/27 15:22:46 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scop.h"

void gl_attr_init(void);
void gl_version_info(void);

void init(t_sdl *sdl)
{
    assert(SDL_Init(SDL_INIT_VIDEO) == 0);
    gl_attr_init();
    sdl->win = SDL_CreateWindow(WINNAME, SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED,
                           WINX, WINY, SDL_WINDOW_OPENGL);
    assert(sdl->win != NULL);
    sdl->ctx = SDL_GL_CreateContext(sdl->win);
    glViewport(0, 0, WINX, WINY);
    glEnable(GL_DEPTH_TEST);
    glewExperimental = 1;
    glewInit();
    SDL_GL_SetSwapInterval(1);
    glClearColor(0.863, 0.863, 0.863, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(sdl->win);
    gl_version_info();
}

void deinit(t_sdl *sdl)
{
    SDL_GL_DeleteContext(sdl->ctx);
    SDL_DestroyWindow(sdl->win);
    SDL_Quit();
}

void gl_attr_init(void)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void gl_version_info(void)
{
    int major_version;
    int minor_version;

    major_version = 0;
    minor_version = 0;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major_version);
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor_version);
    printf("> OpenGL version: %d.%d\n", major_version, minor_version);
}

