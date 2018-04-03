/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 23:30:45 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/02/06 23:30:46 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>
#include <utils.h>

ssize_t	map_index(ssize_t index, char *key, t_hash *table)
{
	insert(key, new_hash_ctx(index), table);
	return (index);
}

void	process_vert_data(t_vert_data *data,
								GLfloat *vbo,
								GLuint *ibo,
								t_model_data *scop_model)
{
	t_hash	*table;
	char	*key;

	table = table_instance(NULL);
	key = keygen(data);
	if (key_exist(key, table))
		append_to_ibo(*(GLuint*)value_of(key, table), ibo);
	else
	{
		append_to_vbo(data, vbo, scop_model);
		append_to_ibo(map_index(*indexgen(), key, table), ibo);
	}
	free(key);
}

void	add_to_buffers(t_face_ctx *ctx,
							GLfloat *vbo,
							GLuint *ibo,
							t_model_data *scop_model)
{
	process_vert_data(&ctx->vert1, vbo, ibo, scop_model);
	process_vert_data(&ctx->vert2, vbo, ibo, scop_model);
	process_vert_data(&ctx->vert3, vbo, ibo, scop_model);
}

void	load(GLfloat *vbo, GLuint *ibo, t_model_data *scop_model)
{
	ssize_t		index;
	ssize_t		max_index;
	t_face_ctx	*data;
	t_hash		*table;

	index = 0;
	max_index = stack_size(&scop_model->faces);
	table = new_table(getpagesize());
	table_instance(table);
	*indexgen() = -1;
	*offset_of(e_vbo) = 0;
	*offset_of(e_ibo) = 0;
	while (index < max_index)
	{
		data = (t_face_ctx*)top(&scop_model->faces);
		add_to_buffers(data, vbo, ibo, scop_model);
		pop(&scop_model->faces);
		++index;
	}
	free((void*)table - sizeof(int));
}

void	load_this(t_scop_object *entry)
{
	GLfloat	*vbo_buffer;
	GLuint	*ibo_buffer;
	int		vbo_size;
	int		ibo_size;

	vbo_size = stack_size(&entry->model.faces) * sizeof(GLfloat) * 8 * 3;
	ibo_size = stack_size(&entry->model.faces) * sizeof(GLuint) * 3;
	entry->gl.idx_num = ibo_size / sizeof(GLuint);
	vbo_buffer = malloc(vbo_size);
	ft_memset(vbo_buffer, 0, vbo_size);
	ibo_buffer = malloc(ibo_size);
	ft_memset(ibo_buffer, 0, ibo_size);
	load(vbo_buffer, ibo_buffer, &entry->model);
	glGenBuffers(1, &entry->gl.vbo);
	glGenBuffers(1, &entry->gl.ibo);
	glGenVertexArrays(1, &entry->gl.vao);
	glBindVertexArray(entry->gl.vao);
	glBindBuffer(GL_ARRAY_BUFFER, entry->gl.vbo);
	glBufferData(GL_ARRAY_BUFFER, vbo_size, vbo_buffer, GL_DYNAMIC_DRAW);
	buffers_attribs(entry->gl.ibo, ibo_buffer, ibo_size);
	glBindVertexArray(0);
	free(vbo_buffer);
	free(ibo_buffer);
}
