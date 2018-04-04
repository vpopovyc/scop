/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delims.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 22:18:30 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/03/13 22:18:31 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>

int	space_delim(int c)
{
	if (c == ' ')
		return (1);
	else
		return (0);
}

int	face_delim(int c)
{
	if (c == 'f' || c == ' ')
		return (1);
	else
		return (0);
}

int	slash_delim(int c)
{
	if (c == '/')
		return (1);
	else
		return (0);
}
