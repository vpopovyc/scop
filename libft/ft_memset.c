/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:51:58 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/02/03 21:52:00 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <libft.h>

void	*ft_memset(void *p, char c, size_t len)
{
	register char 	*r_p;
	register char 	r_c;
	register size_t	i;

	i = len;
	r_p = p;
	r_c = c;
	while (i)
		r_p[--i] = r_c;
	return (r_p);
}
