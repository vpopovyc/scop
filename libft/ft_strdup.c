/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 13:34:54 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/16 13:37:59 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s1)
{
	size_t		i;
	char		*beer;

	i = ft_strlen(s1);
	beer = (char*)malloc(sizeof(char) * (i + 1));
	if (beer)
	{
		*beer = *ft_strcpy(beer, s1);
		return (beer);
	}
	else
		return (NULL);
}
