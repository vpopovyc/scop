/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 13:15:32 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/03/11 13:15:33 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <hash.h>
#include <string.h>
#define TABLESIZE(table) (*(t_uint*)(((void*)(table)) - sizeof(t_uint)))

int		key_exist(char *key, t_hash *table)
{
	t_hash	*iter;
	int		id;

	id = hash_id(str_hash(key), TABLESIZE(table));
	iter = table[id].internal;
	if (ft_strequ(table[id].key, key))
		return (1);
	else
	{
		while (iter)
		{
			if (iter == NULL)
			{
				exit(-1);
			}
			if (ft_strlen(iter->key) == 0)
				iter = iter->internal;
			if (ft_strequ(iter->key, key))
				return (1);
			iter = iter->internal;
		}
	}
	return (0);
}

static t_hash	*append_with(char *key, void *value, t_hash *internal)
{
	t_hash	*iter;
	t_hash	*new;

	new = malloc(sizeof(t_hash));
	memset(new, 0, sizeof(t_hash));
	new->key = strdup(key);
	new->value = value;
	iter = internal;
	if (iter == NULL)
		internal = new;
	else
	{
		while (iter->internal)
			iter = iter->internal;
		iter->internal = new;
	}
	return (internal);
}

void	insert(char *key, void *value, t_hash *table)
{
	int		id;

	id = hash_id(str_hash(key), TABLESIZE(table));
	if (!table[id].key)
	{
		table[id].key = strdup(key);
		table[id].value = value;
	}
	else if (!key_exist(key, table))
		table[id].internal = append_with(key, value, table[id].internal);
}

void	*value_of(char *key, t_hash *table)
{
	int		id;
	t_hash	*iter;

	id = hash_id(str_hash(key), TABLESIZE(table));
	iter = table[id].internal;
	if (ft_strequ(table[id].key, key))
		return (table[id].value);
	else
	{
		while (iter)
		{
			if (ft_strequ(iter->key, key))
				return (iter->value);
			iter = iter->internal;
		}
	}
	return (NULL);
}

t_hash	*new_table(t_uint size)
{
	void *mem;

	mem = malloc((sizeof(t_hash) * size) + sizeof(t_uint));
	if (!mem)
		return (NULL);
	else
	{
		memset(mem, 0, (sizeof(t_hash) * size) + sizeof(t_uint));
		memcpy(mem, &size, sizeof(t_uint)); 
		return (mem + sizeof(t_uint));
	}
}
