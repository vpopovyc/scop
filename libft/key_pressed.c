/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pressed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/24 21:05:50 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/03/24 21:08:17 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <key_pressed.h>

static _Bool	*key(void)
{
	static _Bool key = 0;

	return (&key);
}

_Bool			is_key_pressed(void)
{
	return (key());
}

void			key_pressed(void)
{
	*key() = 1;
}

void			reset_key_press(void)
{
	*key() = 0;
}
