/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayamamo <tayamamo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 18:23:41 by tayamamo          #+#    #+#             */
/*   Updated: 2021/03/27 12:40:31 by tayamamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_free_null(char **ptr)
{
	size_t	len;
	char	*p;

	if (!ptr)
		return ;
	if (*ptr)
	{
		len = ft_strlen(*ptr);
		p = *ptr;
		while (len--)
			*(p++) = '\0';
		free(*ptr);
		*ptr = NULL;
	}
	return ;
}

static int	read_file(char *text[], const int fd)
{
	char	*buf;
	ssize_t	size;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (-1);
	size = read(fd, buf, BUFFER_SIZE);
	if (!size)
	{
		free(buf);
		return (0);
	}
	else if (size < 0)
	{
		free(buf);
		return (-1);
	}
	buf[size] = '\0';
	text[fd] = ft_strjoin_free(text[fd], buf);
	if (!(text[fd]))
		return (-1);
	return (1);
}

static int	set_line(char *text[], const int fd, char **line)
{
	char	*tmp;
	char	*ptr;

	if (ft_strlen(text[fd]))
	{
		ptr = ft_strchr(text[fd], '\n');
		if (ptr == NULL)
		{
			*line = ft_strdup(text[fd]);
			ft_free_null(&(text[fd]));
			return (0);
		}
		*ptr = '\0';
		*line = ft_strdup(text[fd]);
		tmp = ft_strdup(ptr + 1);
		ft_free_null(&(text[fd]));
		text[fd] = tmp;
	}
	else
	{
		*line = ft_strdup(text[fd]);
		ft_free_null(&(text[fd]));
		return (0);
	}
	return (1);
}

static int	check_parameters(int fd, char **line, char *text[])
{
	char	buf[1];

	if (fd < 0 || fd >= 1024 || !line || read(fd, buf, 0) < 0
		|| BUFFER_SIZE < 1)
		return (-1);
	if (text[fd] == NULL)
	{
		text[fd] = ft_strdup("");
		if (text[fd] == NULL)
			return (-1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*text[1024];
	int			ret;

	if (check_parameters(fd, line, text) == -1)
		return (-1);
	while (ft_strchr(text[fd], '\n') == NULL)
	{
		ret = read_file(text, fd);
		if (!ret)
			break ;
		else if (ret == -1)
		{
			ft_free_null(&(text[fd]));
			return (-1);
		}
	}
	return (set_line(text, fd, line));
}
