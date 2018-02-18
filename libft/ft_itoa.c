/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 20:16:49 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/15 17:06:08 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int		ft_len(size_t v, size_t b)
{
	int		ln;

	ln = (v == 0) ? 1 : 0;
	while (v)
	{
		v /= b;
		++ln;
	}
	return (ln);
}

char			*ft_itoa(size_t v, size_t b)
{
	int			ln;
	char		*st;

	if (b < 2 || b > 16)
		return (NULL);
	ln = ft_len(v, b);
    st = ft_strnew((size_t)ln);
	while (--ln >= 0)
	{
		st[ln] = ((v % b) > 9) ? ((char)(v % b) - 10 + 'A') :
								 ((char)(v % b) + '0');
		v /= b;
	}
	return (st);
}
