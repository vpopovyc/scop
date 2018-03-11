/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_id.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 13:17:16 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/03/11 13:17:17 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <hash.h>

t_uint	str_hash(char *sv)
{
	t_uint	hash;

	hash = HASH_FNV;
	while (*sv)
	{
		hash = (MAGIC_NUMBER_FNV * hash) ^ *sv;
		++sv;
	}
	return (hash);
}

t_uint	hash_id(t_uint hash, t_uint sizeoftable)
{
	return (hash % sizeoftable);
}