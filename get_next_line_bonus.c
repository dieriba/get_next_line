/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:41:26 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/09 19:41:26 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*next_lines(char *lines)
{
	size_t	i;
	char	*new_lines;

	i = -1;
	if (lines == NULL)
		return NULL;
	while (lines[++i] && lines[i] != '\n')
		;
	if (lines[i] == 0)
		return NULL;
	return (&lines[i + 1]);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (c == 0)
		return ((char *)(s) + ft_strlen(s));
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

char	*ft_lines(char *lines, char *buffer, int ret, int fd)
{
	while (ret && !ft_strchr(buffer, '\n'))
	{
		ret = read(fd, buffer, BUFFER_SIZE);
		if (ret < 0)
			return (NULL);
		buffer[ret] = '\0';
		lines = ft_strjoin(lines, buffer);
		if (!lines)
			return (NULL);
	}
	return (lines);
}

char	*ft_getlines(char *lines)
{
	size_t	i;
	char	*new_lines;

	i = -1;
	if (lines == NULL)
		return (NULL);
	while (lines[++i] && lines[i] != '\n')
		;
	new_lines = ft_callocs((i + (lines[i] == '\n')), sizeof(char));
	if (!new_lines)
		return (NULL);
	i = -1;
	while (lines[++i] && lines[i] != '\n')
		new_lines[i] = lines[i];
	if (lines[i])
		new_lines[i++] = '\n';
	new_lines[i] = 0;
	return (new_lines);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	static char		*lines[1000];
	char			*res;

	if ((fd < 0) || BUFFER_SIZE < 1 || (read(fd, NULL, 0) < 0))
		return (NULL);
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (NULL);
	lines[fd] = ft_lines(lines[fd], buffer, 1, fd);
	res = ft_getlines(lines[fd]);
	lines[fd] = next_lines(lines[fd]);
	free(buffer);
	return (res);
}
