/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 13:26:53 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/16 13:41:26 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char *s, int c)
{
	char *str;
	int len;

	len = (int)ft_strlen(s);
	while (len-- >= 0)
	{
		if (*s == c)
		{
			str = (char*)s;
			return (str);
		}
		s++;
	}
	return (NULL);
}
