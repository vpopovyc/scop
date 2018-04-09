/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 21:29:40 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/04/04 22:21:41 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stack.h>
#include <stdlib.h>

int		stack_size(t_stack *stack)
{
	int				len;
	t_stack_elem	*i;

	len = 0;
	i = stack->top_node;
	if (i != NULL)
	{
		++len;
		while (i != stack->bot_node)
		{
			++len;
			i = i->bot_elem;
		}
	}
	return (len);
}
