/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 17:43:18 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/27 17:43:40 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>
#include <parse_obj.h>
#include <utils.h>
#include <fcntl.h>

void	process_vert_indice(char **data, t_vert_data *vert)
{
	void	*data_ptr;
	size_t	*p;

	data_ptr = (void*)data;
	p = (size_t*)vert;
	ft_memset(vert, 0, sizeof(t_vert_data));
	if (!data)
		return ;
	while (*data &&
				((size_t)(ptrdiff_t)p - (ptrdiff_t)vert < sizeof(t_vert_data)))
	{
		*p = ft_atoi(*data);
		++p;
		++data;
	}
	ft_ppdel((char***)&data_ptr);
}

void	process_face_indices(char *v_fst, char *v_sec, char *v_thrd,
														t_stack *faces)
{
	t_face_ctx	ctx;

	process_vert_indice(ft_split(v_fst, slash_delim), &ctx.vert1);
	process_vert_indice(ft_split(v_sec, slash_delim), &ctx.vert2);
	process_vert_indice(ft_split(v_thrd, slash_delim), &ctx.vert3);
	enqueue(faces, new_face_ctx(&ctx));
}

void	process_face(char *line, t_stack *faces)
{
	int		i;
	char	**data;

	i = 0;
	data = ft_split(line, face_delim);
	if (!data)
		return ;
	while (data[0] && data[i + 1] && data[i + 2])
	{
		process_face_indices(data[0], data[i + 1], data[i + 2], faces);
		++i;
	}
	ft_ppdel(&data);
}

void	match_type(char type, char *line, t_model_data *model)
{
	if (type == comment)
		printf(">%s\n", line);
	else if (type == object_name)
		printf("> Object: %s\n", line);
	else if (type == face)
		process_face(line, &model->faces);
	else if (type == vertex)
		process_vertex(line, model);
	else
		return ;
}

void	parse_obj(const char *file_path, t_scop_object *entry)
{
	int		fd;
	char	*line;

	assert((fd = open(file_path, O_RDWR)) >= 0);
	while (get_next_line(fd, &line))
	{
		if (ft_is_empty(line))
			;
		else
			match_type(line[0], line, &entry->model);
		free(line);
	}
	object_center_in(&entry->model.vertices);
	close(fd);
}
