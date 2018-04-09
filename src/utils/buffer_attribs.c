/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_buffers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 22:00:31 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/04/03 22:00:46 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>
#include <utils.h>

void	buffers_attribs(GLuint ibo, GLuint *ibo_buffer, GLuint ibo_size)
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ibo_size, ibo_buffer,
											GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat),
											(GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat),
											(GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat),
											(GLvoid*)(6 * sizeof(GLfloat)));
}

void	object_center_in(t_stack *vertices)
{
	size_t			i;
	size_t			vert_num;
	t_axis			center;
	t_vertex_ctx	*ctx;

	vert_num = stack_size(vertices);
	center = (t_axis){0.0f, 0.0f, 0.0f, 1.0f};
	i = 0;
	while (i < vert_num && (ctx = (t_vertex_ctx*)value_at(i, vertices)))
	{
		center[x_axis] += (GLfloat)ctx->x;
		center[y_axis] += (GLfloat)ctx->y;
		center[z_axis] += (GLfloat)ctx->z;
		++i;
	}
	center = qdiv(center, vert_num);
	i = 0;
	while (i < vert_num && (ctx = (t_vertex_ctx*)value_at(i, vertices)))
	{
		ctx->x -= center[x_axis];
		ctx->y -= center[y_axis];
		ctx->z -= center[z_axis];
		++i;
	}
}
