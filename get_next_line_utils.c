/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 11:32:54 by tayamamo          #+#    #+#             */
/*   Updated: 2021/03/25 17:00:47 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	while (*(s++))
		cnt++;
	return (cnt);
}

char	*ft_strdup(const char *src)
{
	size_t		len;
	char		*copy;
	char		*d;
	const char	*s;

	len = ft_strlen(src) + 1;
	copy = malloc(len);
	if (copy == NULL)
		return (NULL);
	d = copy;
	s = src;
	if (d == NULL && s == NULL)
		return (copy);
	while (len--)
		*(d++) = *(s++);
	return (copy);
}

char	*ft_strchr(const char *s, int c)
{
	if (*s == c)
		return ((char *)s);
	else
	{
		while (*(s++))
			if (*s == c)
				return ((char *)s);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	char	*res;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s = malloc(sizeof(char) * (len1 + len2 + 1));
	if (s == NULL)
		return (NULL);
	res = s;
	while (len1--)
		*s++ = *s1++;
	while (len2--)
		*s++ = *s2++;
	*s = '\0';
	return (res);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}
