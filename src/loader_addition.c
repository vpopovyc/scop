/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_addition.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 21:50:04 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/04/03 21:50:06 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>
#include <utils.h>

t_hash	*table_instance(t_hash *ptr)
{
	static t_hash	*stored_ptr;

	if (ptr)
		stored_ptr = ptr;
	return (stored_ptr);
}

ssize_t	*indexgen(void)
{
	static ssize_t	index = -1;

	++index;
	return (&index);
}

ssize_t	*offset_of(t_buffer_type type)
{
	static ssize_t	vbo_offset = 0;
	static ssize_t	ibo_offset = 0;

	if (type == e_vbo)
		return (&vbo_offset);
	else if (type == e_ibo)
		return (&ibo_offset);
	else
		return (NULL);
}

void	append_to_ibo(GLuint index, GLuint *ibo)
{
	ssize_t	*offset;

	offset = offset_of(e_ibo);
	ibo[*offset] = index;
	++*offset;
}

void	append_to_vbo(t_vert_data *data, GLfloat *vbo, t_model_data *scop_model)
{
	ssize_t				*offset;
	static t_vertex_ctx	fallback = (t_vertex_ctx){0.0f, 0.0f, 0.0f};
	void				*value;
	t_vertex_ctx		vert;

	offset = offset_of(e_vbo);
	value = value_at(data->vertex - 1, &scop_model->vertices);
	vert = value ? *(t_vertex_ctx*)value : fallback;
	vbo[*offset] = (GLfloat)vert.x;
	vbo[++*offset] = (GLfloat)vert.y;
	vbo[++*offset] = (GLfloat)vert.z;
	value = value_at(data->normal - 1, &scop_model->normals);
	vert = (value ? *(t_vertex_ctx*)value : fallback);
	vbo[++*offset] = (GLfloat)vert.x;
	vbo[++*offset] = (GLfloat)vert.y;
	vbo[++*offset] = (GLfloat)vert.z;
	value = value_at(data->texture - 1, &scop_model->texels);
	vert = value ? *(t_vertex_ctx*)value : fallback;
	vbo[++*offset] = (GLfloat)vert.x;
	vbo[++*offset] = (GLfloat)vert.y;
	++*offset;
}
