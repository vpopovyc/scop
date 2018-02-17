/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <vpopovyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/16 13:36:14 by vpopovyc          #+#    #+#             */
/*   Updated: 2017/09/16 13:43:12 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*beer;

	if (!(beer = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_memset(beer, '\0', size + 1);
	return (beer);
}
