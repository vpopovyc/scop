/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vpopovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 21:56:30 by vpopovyc          #+#    #+#             */
/*   Updated: 2018/02/03 21:56:31 by vpopovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	ft_count_words(char *s, char c)
{
	size_t		i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s != c && *s)
				s++;
			if (*s == '\0')
				break ;
		}
		s++;
	}
	return (i);
}

static size_t	ft_count_chars(char *s, char c)
{
	size_t		i;

	i = 0;
	while (*s != c && *s)
	{
		i++;
		s++;
	}
	return (i);
}

char			**ft_strsplit(char *s, char c)
{
	char		**p2p;
	size_t		len;
	size_t		i;

	if (!s)
		return (NULL);
	if (!(p2p = (char**)malloc(sizeof(char*) * (ft_count_words(s, c) + 1))))
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = ft_count_chars(s, c);
			p2p[i] = ft_strnew(len);
			ft_strncpy(p2p[i++], s, len);
			s += len;
		}
		if (*s == '\0')
			break ;
		s++;
	}
	p2p[i] = NULL;
	return (p2p);
}
