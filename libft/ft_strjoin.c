/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 13:30:31 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/16 13:38:06 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	char	*beer;

	beer = NULL;
	if (s1 && s2)
	{
		i = ft_strlen(s1) + ft_strlen(s2);
		if ((beer = ft_strnew(i)))
			beer = ft_strcat(ft_strcpy(beer, s1), s2);
	}
	return (beer);
}
