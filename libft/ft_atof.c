/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 20:08:26 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/02/03 20:08:28 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

float	ft_atof(const char *p)
{
	float	result;
	float	fract;
	_Bool	minus;

	fract = 1.0f;
	result = 0.0f;
	minus = 0;
	while ((*p >= '\t' && *p <= '\r') || *p == ' ')
		++p;
	minus = *p == '-' ? 1 : 0;
	*p == '-' || *p == '+' ? ++p : p;
	while (*p >= '0' && *p <= '9')
	{
		result = result * 10.0f + (*p - '0');
		++p;
	}
	*p == '.' ? ++p : p;
	while (*p >= '0' && *p <= '9')
	{
		fract *= 0.1;
		result += (*p - '0') * fract;
		++p;
	}
	return (minus ? -result : result);
}
