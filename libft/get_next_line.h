/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 13:24:02 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/16 13:42:27 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H 
# include "libft.h"
# define BUFF_SIZE 512

typedef struct		s_gnl
{
	char			*brb;
	char			*pimp;
	char			*adr;
	long			nbytes;
	struct s_gnl	*next;
	int				fd;
	char 			padding[4];
}					t_gnl;
int					get_next_line(const int fd, char **line);

#endif
