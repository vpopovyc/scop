/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 17:21:33 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/03/13 22:40:21 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stack.h>
#include <stdlib.h>

int         stack_size(t_stack *stack)
{
    int            len;
    t_stack_elem   *i;

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

void    *value_at(unsigned long index, t_stack *stack)
{
    unsigned long  i;
    t_stack_elem   *res;

    i = 0;
    res = stack->top_node;
    if (res != NULL)
    {
        while (i != index)
        {
            res = res->bot_elem;
            ++i;
        }
        return (res->context);
    }
    return (NULL);
}

void   *top(t_stack *stack)
{
    return (stack->top_node->context);
}

void        pop(t_stack *stack)
{
    t_stack_elem *stack_elem_for_free;

    if (stack->top_node == NULL)
        return ;
    else
    {
        stack_elem_for_free = stack->top_node;
        stack->top_node = stack_elem_for_free->bot_elem;
        if (stack->top_node != NULL)
            stack->top_node->top_elem = NULL;
        free(stack_elem_for_free->context);
        free(stack_elem_for_free);
    }
}

void        push(t_stack *stack, void *context)
{
    t_stack_elem *new_elem;

    new_elem = (t_stack_elem*)malloc(sizeof(t_stack_elem));
    new_elem->context = context;
    new_elem->top_elem = NULL;
    new_elem->bot_elem = NULL;
    if (stack->top_node == NULL)
    {
        stack->top_node = new_elem;
        stack->bot_node = new_elem;
    }
    else
    {
        stack->top_node->top_elem = new_elem;
        new_elem->bot_elem = stack->top_node;
        stack->top_node = new_elem;
    }
}

void    enqueue(t_stack *stack, void *context)
{
    t_stack_elem *new_elem;

    new_elem = (t_stack_elem*)malloc(sizeof(t_stack_elem));
    new_elem->context = context;
    new_elem->top_elem = NULL;
    new_elem->bot_elem = NULL;
    if (stack->top_node == NULL)
    {
        stack->top_node = new_elem;
        stack->bot_node = new_elem;
    }
    else
    {
        stack->bot_node->bot_elem = new_elem;
        new_elem->top_elem = stack->bot_node;
        stack->bot_node = new_elem;
    }
}
