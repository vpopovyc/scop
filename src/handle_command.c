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

GLfloat g_rot_x = 0.0f;
GLfloat g_rot_y = 0.0f;
GLfloat g_rot_z = 0.0f;
GLfloat g_scale_factor = 1.0f;
t_axis  g_current_axis = (t_axis){0.0f, 0.0f, 0.0f, 1.0f};

static inline void __exit(int excode)
{
    deinit();
    exit(excode);
}

void update_axis(t_axis_type type)
{
    if (type == x_axis)
    {
        g_gl.lcs.x = quat(1.0f, 0.0f, 0.0f, g_rot_x);
    }
    else if (type == y_axis)
    {
        g_gl.lcs.y = quat(0.0f, 1.0f, 0.0f, g_rot_y);
    }
    else
    {
        g_gl.lcs.z = quat(0.0f, 0.0f, 1.0f, g_rot_z);    
    }
}

void set_model_matrix(void)
{
    GLuint  rotate_matrix_id;
    GLuint  scale_matrix_id;
    GLuint  translate_matrix_id;

    GLfloat scale_matrix[16];
    GLfloat rotate_matrix[16];
    GLfloat translate_matrix[16];

    g_gl.quat = qmul(qmul(g_gl.lcs.y, g_gl.lcs.x), g_gl.lcs.z);

    rotate_matrix_id = glGetUniformLocation(g_gl.shader_program, "rotation_matrix");
    scale_matrix_id = glGetUniformLocation(g_gl.shader_program, "scale_matrix");
    translate_matrix_id = glGetUniformLocation(g_gl.shader_program, "translate_matrix");

    identy_m44(scale_matrix);
    identy_m44(translate_matrix);

    // Scale
    scale_m44(g_scale_factor, scale_matrix);
    // Rotations
    quat_to_m44(&g_gl.quat, rotate_matrix);
    // Translation
    translation_m44(&g_current_axis, translate_matrix);

    glUniformMatrix4fv(rotate_matrix_id, 1, GL_FALSE, rotate_matrix);
    glUniformMatrix4fv(scale_matrix_id, 1, GL_FALSE, scale_matrix);
    glUniformMatrix4fv(translate_matrix_id, 1, GL_FALSE, translate_matrix);
}

void set_mvp(void)
{
    set_model_matrix();
}

void draw(void)
{
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUseProgram(g_gl.shader_program);
    set_mvp();
    glBindTexture(GL_TEXTURE_2D, g_gl.tex);
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
            g_rot_y += 5.0f;
            update_axis(y_axis);
            key_pressed = 1;
        }
        if (keystate[SDL_SCANCODE_L])
        {
            g_rot_y -= 5.0f;
            update_axis(y_axis);
            key_pressed = 1;
        }
        if (keystate[SDL_SCANCODE_J])
        {
            g_rot_x += 5.0f;
            update_axis(x_axis);
            key_pressed = 1;
        }
        if (keystate[SDL_SCANCODE_K])
        {
            g_rot_x -= 5.0f;
            update_axis(x_axis);
            key_pressed = 1;
        }
        if (keystate[SDL_SCANCODE_U])
        {
            g_rot_z += 5.0f;
            update_axis(z_axis);
            key_pressed = 1;
        }
        if (keystate[SDL_SCANCODE_I])
        {
            g_rot_z -= 5.0f;
            update_axis(z_axis);
            key_pressed = 1;
        }
        if (g_gl.event.wheel.y == 1)
        {
            g_scale_factor += g_scale_factor + 0.1f > 1.5f ? 0.0f : 0.1f;
            key_pressed = 1;
        }
        if (g_gl.event.wheel.y == -1)
        {
            g_scale_factor -= g_scale_factor - 0.1f > 0.1f ? 0.1f : 0.0f;
            key_pressed = 1;
        }
        if (keystate[SDL_SCANCODE_X])
        {
            g_current_axis[0] += 0.009f;
            key_pressed = 1;
        }
        if (keystate[SDL_SCANCODE_Z])
        {
            g_current_axis[0] -= 0.009f;
            key_pressed = 1;
        }
        if (keystate[SDL_SCANCODE_V])
        {
            g_current_axis[1] += 0.009f;
            key_pressed = 1;
        }
        if (keystate[SDL_SCANCODE_C])
        {
            g_current_axis[1] -= 0.009f;
            key_pressed = 1;
        }
        if (keystate[SDL_SCANCODE_N])
        {
            g_current_axis[2] += 0.009f;
            key_pressed = 1;
        }
        if (keystate[SDL_SCANCODE_B])
        {
            g_current_axis[2] -= 0.009f;
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
