/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 13:18:02 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/03/11 13:18:06 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __HASH_H
# define __HASH_H

# include <libft.h>

# define MAGIC_NUMBER_FNV	16777619
# define HASH_FNV			2166136261
# define SIZEOFTABLE		64

typedef unsigned			t_uint;

/*
** type and memory safety of value is managed on client side
*/

typedef struct				s_hash
{
	char					*key;
	void					*value;
	struct s_hash			*internal;
}							t_hash;

/*
**	hash.c
*/

void						*value_of(char *key, t_hash *table);
void						insert(char *key, void *value, t_hash *table);
int							key_exist(char *key, t_hash *table);
t_hash						*new_table(t_uint size);
/*
** hash_id.c
*/

t_uint						str_hash(char *sv);
t_uint						hash_id(t_uint hash, t_uint sizeoftable);

#endif
