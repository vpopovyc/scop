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

void check_compile_errors(void)
{
    GLint   success;
    GLchar  log[512];

    glGetShaderiv(g_gl.vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
        print_error_log(g_gl.vertex_shader, log);
    glGetShaderiv(g_gl.fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
        print_error_log(g_gl.fragment_shader, log);
    glGetProgramiv(g_gl.shader_program, GL_LINK_STATUS, &success);
    if (!success)
        print_error_log(g_gl.fragment_shader, log);
}

void compile_shaders(void)
{
    const char    *vert_shader;
    const char    *frag_shader;

    // Vertex shader
    g_gl.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    vert_shader = reader("src/shaders/vertex.glsl");
    const GLchar *const * ptr = &vert_shader;
    glShaderSource(g_gl.vertex_shader, 1, ptr, NULL);
    glCompileShader(g_gl.vertex_shader);
    // Fragment shader
    g_gl.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    frag_shader = reader("src/shaders/fragment.glsl");
    const GLchar *const * ptr2 = &frag_shader;
    glShaderSource(g_gl.fragment_shader, 1, ptr2, NULL);
    glCompileShader(g_gl.fragment_shader);
    // Program
    g_gl.shader_program = glCreateProgram();
    glAttachShader(g_gl.shader_program, g_gl.vertex_shader);
    glAttachShader(g_gl.shader_program, g_gl.fragment_shader);
    glLinkProgram(g_gl.shader_program);

    check_compile_errors();

    glDeleteShader(g_gl.fragment_shader);
    glDeleteShader(g_gl.vertex_shader);


}
