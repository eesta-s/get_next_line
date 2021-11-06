/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eesta <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 17:44:10 by eesta             #+#    #+#             */
/*   Updated: 2021/05/13 21:33:28 by eesta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*strl_cpy(const char *s1)
{
	char	*s;
	size_t	i;

	s = malloc(str_len(s1) + 1);
	i = 0;
	if (!s)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = 0;
	return (s);
}

char	*sub_str(char const *s, unsigned int start, size_t n)
{
	char	*str;
	size_t	i;

	str = malloc(n + 1);
	i = 0;
	if (str == NULL)
		return (NULL);
	while (i < n && i + start < str_len(s))
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*poisk_chr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

int	get_line(int rf, char **nl, char **line)
{
	char	*str;

	if (rf == 0)
		*line = strl_cpy(*nl);
	else if (rf > 0)
		*line = sub_str(*nl, 0, (poisk_chr(*nl) - *nl));
	else
	{
		free(*nl);
		return (-1);
	}
	str = strl_cpy(*nl + (str_len(*line)) + 1);
	mem_set(*nl, 0, str_len(*nl));
	free(*nl);
	*nl = NULL;
	*nl = str;
	if (rf == 0)
	{
		mem_set(*nl, 0, str_len(*nl));
		free(*nl);
		*nl = NULL;
	}
	return (rf);
}

int	get_next_line(int fd, char **line)
{
	int			c;
	int			rf;
	static char	*nl;
	char		*buf;

	rf = 1;
	if (nl == NULL)
		nl = get_read_join(nl);
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (!poisk_chr(nl) && rf > 0)
	{		
		rf = read(fd, buf, BUFFER_SIZE);
		buf[rf] = 0;
		nl = malloc_join(nl, buf);
	}
	free(buf);
	c = get_line(rf, &nl, line);
	if (c == 0)
		return (0);
	else if (c > 0)
		return (1);
	return (-1);
}
