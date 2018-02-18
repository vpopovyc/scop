/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvolovik <rvolovik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/06 14:33:22 by rvolovik          #+#    #+#             */
/*   Updated: 2017/06/05 13:40:12 by rvolovik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int        word_len_in_str(char *string, int (*compare)(int))
{
    int        len;
    char    *ptr;

    len = 0;
    ptr = string;
    while (!compare(*ptr) && *ptr)
    {
        len++;
        ptr++;
    }
    return (len);
}

static int        count_words_in_string(char *string, int (*compare)(int))
{
    char    *ptr;
    int        words;

    ptr = string;
    words = 0;
    if (string)
    {
        while (*ptr)
        {
            if (!compare(*ptr))
            {
                words++;
                ptr += word_len_in_str(ptr, compare);
                continue ;
            }
            ptr++;
        }
    }
    return (words);
}

static char         *ft_strsub(char const *s, unsigned int start, size_t len)
{
    size_t    i;
    char    *beer;

    i = 0;
    beer = NULL;
    if (s && (beer = ft_strnew(len)))
        while (i < len)
            beer[i++] = s[start++];
    return (beer);
}

char            **ft_split(char *string, int (*compare)(int))
{
    char    *s;
    char    **new;
    int        i;
    int        words;

    s = string;
    i = 0;
    words = count_words_in_string(string, compare);
    if (words == 0)
        return ((char**)NULL);
    new = (char**)malloc(sizeof(char*) * (words + 1));
    new[words] = NULL;
    while (*s && i < words)
    {
        if (!compare(*s))
        {
            new[i++] = ft_strsub(s, 0, word_len_in_str(s, compare));
            s += word_len_in_str(s, compare);
            continue ;
        }
        s++;
    }
    return (new);
}
