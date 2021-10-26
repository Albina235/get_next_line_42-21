/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evalorie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:37:45 by evalorie          #+#    #+#             */
/*   Updated: 2021/10/26 18:48:47 by evalorie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_lstrjoin(char *line, char *buff)
{
	char	*s;

	s = (char *)malloc((ft_strlen(line) + ft_strlen(buff) + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	while (*line)
	{
		*s = *line;
		line++;
		s++;
	}
	while (*buff)
	{
		*s= *buff;
		s++;
		buff++;
	}
	*s = '\0';
	free(line);
	return (s);
}

void	ft_last(char *buff, char *last)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buff[i] != '\n')
		i++;
	i++;
	free(last);
	last = (char *)malloc(i * sizeof(char));
	while (buff[i])
	{
		last[j] = buff[i];
		j++;
		i++;
	}
	last[j] = '\0';
}

char	*ft_readline(int fd, char *buff, char *last)
{
	char	*line;
	int		i;
	int		trigger;

	i = 0;
	trigger = 0;
	line = NULL;
	line = ft_lstrjoin(line, last);
	while (1)
	{
		buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		read(fd, buff, BUFFER_SIZE);
		while (i < BUFFER_SIZE)
		{
			if (buff[i] == '\n')
			{
				ft_last(buff + i, last);
				buff[i] = '\0';
				trigger = 1;
			}
			i++;
		}
		if (trigger == 1)
			break ;
		line = ft_lstrjoin(line, buff);
		free(buff);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char	*buff;
	static char	*last;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = NULL;
	line = ft_readline(fd, buff, last);
	return (line);
}
