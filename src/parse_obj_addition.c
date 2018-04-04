/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_addition.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 20:35:49 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/04/04 20:35:50 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>
#include <parse_obj.h>
#include <utils.h>

static void	generic_reader(char **data, float *buffer, const size_t n)
{
	register float		*buffer_iter;
	register const char	**data_iter;

	data_iter = (const char **)data;
	buffer_iter = buffer;
	ft_memset(buffer, 0, n);
	while (*++data_iter)
	{
		*buffer_iter = ft_atof(*data_iter);
		++buffer_iter;
	}
	ft_ppdel(&data);
}

static void	read_vertices(char **data, t_stack *vertices)
{
	float buff[4];

	generic_reader(data, buff, sizeof(buff));
	enqueue(vertices, new_ctx(vertex, buff[0], buff[1], buff[2]));
}

static void	read_texels(char **data, t_stack *texels)
{
	float buff[2];

	generic_reader(data, buff, sizeof(buff));
	enqueue(texels, new_ctx(vertex_texture, buff[0], buff[1]));
}

static void	read_normal(char **data, t_stack *normals)
{
	float buff[4];

	generic_reader(data, buff, sizeof(buff));
	enqueue(normals, new_ctx(vertex_normal, buff[0], buff[1], buff[2]));
}

void		process_vertex(char *line, t_model_data *model)
{
	char opt_type;

	if (ft_strlen(line) > 1)
		opt_type = line[1];
	else
		opt_type = 0;
	if (opt_type == vertex_texture)
		read_texels(ft_split(line, space_delim), &model->texels);
	else if (opt_type == vertex_normal)
		read_normal(ft_split(line, space_delim), &model->normals);
	else
		read_vertices(ft_split(line, space_delim), &model->vertices);
}
