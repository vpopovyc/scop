/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 16:40:19 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/16 16:47:22 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_strcmp(const char *s1, const char *s2)
{
	int					i;
	unsigned char		*pt1;
	unsigned char		*pt2;

	pt1 = (unsigned char*)s1;
	pt2 = (unsigned char*)s2;
	while ((*pt1) || (*pt2))
	{
		if (*pt1 != *pt2)
		{
			i = *pt1 - *pt2;
			return (i);
		}
		pt1++;
		pt2++;
	}
	return (0);
}

int		ft_strequ(char const *s1, char const *s2)
{
	if (s1 && s2)
	{
		if (ft_strcmp(s1, s2) == 0)
			return (1);
	}
	return (0);
}
