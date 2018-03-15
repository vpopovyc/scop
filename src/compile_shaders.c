/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile_shaders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 21:43:35 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/02/07 21:43:37 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../scop.h"

char *reader(const char *path)
{
    FILE *fp;
    long size;
    char *data;

    assert((fp = fopen(path, "r")));
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    rewind(fp);
    data = malloc(size + 1);
    data[size] = 0;
    fread(data, size, 1, fp);
    fclose(fp);
    return (data);
}

void print_error_log(GLuint shader, GLchar *log)
{
    glGetShaderInfoLog(shader, 512, NULL, log);
    perror(log);
}

void check_compile_errors(GLuint shader_program, GLuint fragment_shader, GLuint vertex_shader)
{
    GLint   success;
    GLchar  log[512];

    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
        print_error_log(vertex_shader, log);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
        print_error_log(fragment_shader, log);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    if (!success)
        print_error_log(fragment_shader, log);
}

void compile_shaders(t_gl *gl)
{
    const GLchar *vert_shader;
    const GLchar *frag_shader;
    GLuint        fragment_shader;
    GLuint        vertex_shader;

    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    vert_shader = reader("src/shaders/vertex.glsl");
    glShaderSource(vertex_shader, 1, &vert_shader, NULL);
    glCompileShader(vertex_shader);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    frag_shader = reader("src/shaders/fragment.glsl");
    glShaderSource(fragment_shader, 1, &frag_shader, NULL);
    glCompileShader(fragment_shader);
    gl->shader_program = glCreateProgram();
    glAttachShader(gl->shader_program, vertex_shader);
    glAttachShader(gl->shader_program, fragment_shader);
    glLinkProgram(gl->shader_program);
    check_compile_errors(gl->shader_program, vertex_shader, fragment_shader);
    glDeleteShader(fragment_shader);
    glDeleteShader(vertex_shader);
    free(*(void**)&vert_shader);
    free(*(void**)&frag_shader);
}
