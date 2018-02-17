/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ppdel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:58:27 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/02/03 21:58:28 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_ppdel(char ***sv)
{
	char	i;

	i = 0;
	if (*sv != NULL && **sv != NULL)
	{
		while (**sv)
		{
			free(**sv);
			**sv = NULL;
			++(*sv);
			++i;
		}
		*sv -= i;
		free(*sv);
		*sv = NULL;
	}
}
