/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 21:25:10 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/03/24 21:25:11 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scop.h"

static void fill_uniforms(GLfloat *sm, GLfloat *rm, GLfloat *tm, t_gl *gl)
{
    GLuint  rotate_matrix_id;
    GLuint  scale_matrix_id;
    GLuint  translate_matrix_id;

    rotate_matrix_id = glGetUniformLocation(gl->shader_program, "rm");
    scale_matrix_id = glGetUniformLocation(gl->shader_program, "sm");
    translate_matrix_id = glGetUniformLocation(gl->shader_program, "tm");
    glUniformMatrix4fv(rotate_matrix_id, 1, GL_FALSE, rm);
    glUniformMatrix4fv(scale_matrix_id, 1, GL_FALSE, sm);
    glUniformMatrix4fv(translate_matrix_id, 1, GL_FALSE, tm);
}

void set_model_matrix(t_gl *gl, t_cs *cs)
{
    static GLfloat scale_matrix[16];
    static GLfloat rotate_matrix[16];
    static GLfloat translate_matrix[16];
    t_float4 identy_quat;

    identy_quat = quat(0.0f, 0.0f, 0.0f, 1.0f);
    identy_quat = qmul(qmul(cs->y, cs->x), cs->z);
    identy_m44(scale_matrix);
    identy_m44(translate_matrix);
    scale_m44(cs->s, scale_matrix);
    quat_to_m44(&identy_quat, rotate_matrix);
    translation_m44(&cs->o, translate_matrix);
    fill_uniforms(scale_matrix, rotate_matrix, translate_matrix, gl);
}

void draw(t_sdl *sdl, t_scop_object *entry, t_scop_object *skybox)
{
        //     glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUseProgram(entry->gl.shader_program);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    set_model_matrix(&entry->gl, &entry->cs);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, entry->gl.tex);

    glBindVertexArray(entry->gl.vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, entry->gl.ibo);
    glDrawElements(GL_TRIANGLES, entry->gl.idx_num, GL_UNSIGNED_INT, 0);

    set_model_matrix(&skybox->gl, &skybox->cs);

    glBindVertexArray(skybox->gl.vao);
    glBindTexture(GL_TEXTURE_2D, skybox->gl.tex);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skybox->gl.ibo);
    glDrawElements(GL_TRIANGLES, skybox->gl.idx_num, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    SDL_GL_SwapWindow(sdl->win);
    reset_key_press();
}

