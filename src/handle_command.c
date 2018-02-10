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

GLfloat rot_y = 0.0f;
GLfloat rot_vec_buff[3] = {0.0f, 1.0f, 0.0f};

void draw(void)
{
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    printf("draw\n");
    glUseProgram(g_gl.shader_program);
        // Uniforms
    g_gl.rot_y_uniform = glGetUniformLocation(g_gl.shader_program, "rot_y");

    g_gl.rot_vec_uniform = glGetUniformLocation(g_gl.shader_program, "rot_vec");

    glUniform1f(g_gl.rot_y_uniform, rot_y);
    glUniform3fv(g_gl.rot_vec_uniform, 1, rot_vec_buff);

    glBindVertexArray(g_gl.vao);
    glDrawElements(GL_TRIANGLES, g_gl.idx_num, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void handle_command(void)
{
    uint8_t *keystate;
    _Bool   key_pressed;
    

    key_pressed = 0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw();
    SDL_GL_SwapWindow(g_gl.win);
    while (1)
    {
        keystate = (unsigned char *)SDL_GetKeyboardState(NULL);
        SDL_PollEvent(&g_gl.event);
        if ((g_gl.event.type == SDL_QUIT) || keystate[SDL_SCANCODE_ESCAPE])
            __exit(0);
        if (keystate[SDL_SCANCODE_H])
        {
            rot_y += 0.01f;
            rot_vec_buff[1] = 1.0f;
            key_pressed = 1;
        }
        if (keystate[SDL_SCANCODE_L])
        {
            rot_y -= 0.01f;
            rot_vec_buff[1] = 1.0f;
            key_pressed = 1;
        }
        if (keystate[SDL_SCANCODE_J])
        {
            rot_y += 0.01f;
            rot_vec_buff[0] = 1.0f;
            key_pressed = 1;
        }
        if (keystate[SDL_SCANCODE_K])
        {
            rot_y -= 0.01f;
            rot_vec_buff[0] = 1.0f;
            key_pressed = 1;
        }
        if (key_pressed)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            draw();
            SDL_GL_SwapWindow(g_gl.win);
            key_pressed = 0;
        }
    }
}
