/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eesta <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:45:00 by eesta             #+#    #+#             */
/*   Updated: 2021/05/13 21:25:14 by eesta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	str_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

char	*get_read_join(char *nl)
{
	nl = malloc(sizeof(char) * 1);
	nl[0] = 0;
	return (nl);
}

void	*mem_set(void *dest, int c, size_t n)
{
	unsigned char	*cr;
	size_t			i;

	cr = dest;
	i = 0;
	while (i < n)
	{
		cr[i] = c;
		i++;
	}
	return (dest);
}

void	*mem_move(void *dst, const void *src, size_t n)
{
	char	*a;
	char	*b;

	a = (char *)dst;
	b = (char *)src;
	if (dst == src)
		return (dst);
	if (b < a)
	{
		while (n--)
			*(a + n) = *(b + n);
		return (dst);
	}
	while (n--)
		*a++ = *b++;
	return (dst);
}

char	*malloc_join(char const *s1, char const *s2)
{
	size_t	a;
	size_t	b;
	size_t	s3;
	char	*c;

	if (!s1 && !s2)
		return (0);
	a = str_len((char *)s1);
	b = str_len((char *)s2);
	s3 = a + b + 1;
	c = (char *)malloc(str_len(s1) + str_len(s2) + 1);
	if (!c)
		return (NULL);
	mem_move(c, s1, a);
	mem_move(c + a, s2, b);
	c[s3 - 1] = 0;
	free((char *)s1);
	return (c);
}
