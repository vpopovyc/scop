/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:45:59 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/02/03 21:46:01 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <libft.h>

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	register char	*p_d;
	register char	*p_s;
	register size_t	i;
	register size_t	i_max;

	p_d = dst;
	p_s = src;
	i_max = n;
	i = 0;
	while (i < i_max)
	{
		p_d[i] = p_s[i];
		++i;
	}
	return (p_d);
}
