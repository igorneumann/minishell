/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ineumann <ineumann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 13:46:10 by narroyo-          #+#    #+#             */
/*   Updated: 2021/05/25 21:06:59 by ineumann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char			*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

static void			ft_strdel(char **str)
{
	if (str != NULL && *str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

int					ft_print(int fd, char **str, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[fd][i] != '\n')
		i++;
	*line = ft_substr(str[fd], 0, i);
	tmp = ft_strdup(&str[fd][i + 1]);
	free(str[fd]);
	str[fd] = tmp;
	return (1);
}

int					ft_output(int read_return, int fd, char **str, char **line)
{
	if (read_return < 0)
		return (-1);
	else if (read_return == 0 && (str[fd] == NULL || str[fd][0] == '\0'))
	{
		*line = ft_strdup("");
		ft_strdel(&str[fd]);
		return (0);
	}
	else if (ft_strchr(str[fd], '\n'))
		return (ft_print(fd, str, line));
	else
	{
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
		return (0);
	}
}

int					get_next_line(int fd, char **line)
{
	int			read_return;
	char		*buffer;
	char		*tmp;
	static char *str[4096];

	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	if (!(buffer = (char*)malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	while ((read_return = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_return] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(str[fd], buffer);
			free(str[fd]);
			str[fd] = tmp;
		}
		if (ft_strchr(str[fd], '\n'))
			break ;
	}
	free(buffer);
	return (ft_output(read_return, fd, str, line));
}
