/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 15:12:12 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/01/27 15:12:13 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STACK_H
# define __STACK_H

typedef struct s_stack      t_stack;
typedef struct s_stack_elem t_stack_elem;

typedef struct              s_stack_elem
{
	t_stack_elem            *top_elem;
	t_stack_elem            *bot_elem;
	void                    *context;
}                           t_stack_elem;

typedef struct              s_stack
{
	t_stack_elem            *top_node;
	t_stack_elem            *bot_node;
}                           t_stack;

void						enqueue(t_stack *stack, void *context);
void						push(t_stack *stack, void *context);
void						pop(t_stack *stack);
void						*top(t_stack *stack);
int							stack_size(t_stack *stack);

#endif
