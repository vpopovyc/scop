/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 13:20:22 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/16 13:23:10 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_gnl	*ft_gnlnew(const int fd)
{
	t_gnl	*lst;

	if ((lst = malloc(sizeof(t_gnl))) == NULL)
		return (NULL);
	lst->brb = NULL;
    lst->pimp = malloc(sizeof(char));
    lst->pimp[0] = '\0';
	lst->next = NULL;
	lst->fd = fd;
	lst->nbytes = 0;
	return (lst);
}

static void		ft_gnl_pushback(t_gnl **list, t_gnl *fdnode)
{
	t_gnl	*head;

	head = *list;
	while (head->next != NULL)
		head = head->next;
	head->next = fdnode;
}

static t_gnl	*ft_get_chunk(t_gnl **list, const int fd)
{
	t_gnl	*head;

	head = *list;
	while (head)
	{
		if (head->fd == fd)
			return (head);
		head = head->next;
	}
	if ((head = ft_gnlnew(fd)) == NULL)
		return (NULL);
	ft_gnl_pushback(list, head);
	return (head);
}

static int		ft_nmove(t_gnl **ls, char **line)
{
	if (ft_strlen((*ls)->pimp) > 0)
	{
		if ((*ls)->adr != NULL)
			*((*ls)->adr) = '\0';
		*line = ft_strdup((*ls)->brb);
		if ((*ls)->adr != NULL)
			ft_strncpy((*ls)->brb, ++(*ls)->adr, ft_strlen((*ls)->adr) + 1);
		else
			*((*ls)->brb) = '\0';
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	t_gnl			*chunk;
	static t_gnl	*list_of_chunks;

	if ((fd < 0 || read(fd, buf, 0) == -1 || line == NULL || BUFF_SIZE <= 0))
		return (-1);
	if (!list_of_chunks)
		if ((list_of_chunks = ft_gnlnew(fd)) == NULL)
			return (-1);
	if ((chunk = ft_get_chunk(&list_of_chunks, fd)) == NULL)
		return (-1);
	while (!(chunk->adr = ft_strchr(chunk->pimp, '\n')))
	{
		if ((chunk->nbytes = read(fd, buf, BUFF_SIZE)) == -1)
			return (-1);
		if (chunk->nbytes == 0)
			return (ft_nmove(&chunk, line));
		buf[chunk->nbytes] = '\0';
		chunk->brb = ft_strjoin(chunk->pimp, buf);
		free(chunk->pimp);
		chunk->pimp = chunk->brb;
	}
	return (ft_nmove(&chunk, line));
}
