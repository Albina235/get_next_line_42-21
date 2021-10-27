/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evalorie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:37:45 by evalorie          #+#    #+#             */
/*   Updated: 2021/10/27 16:25:50 by evalorie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *line, char *buff)
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
	while (*buff || *(buff - 1) == '\n')
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
	{
		if (buff[i] == '\0')
		{
			free(last);
			return ;
		}
		i++;
	}
	free(last);
	last = (char *)malloc((BUFFER_SIZE - i) * sizeof(char));
	i++;
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
	line = ft_strjoin(line, last);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (1)
	{
		read(fd, buff, BUFFER_SIZE);
		buff[BUFFER_SIZE] = '\0';
		while (i < BUFFER_SIZE)
		{
			if (buff[i] == '\n' || buff[i] == '\0')
			{
				ft_last(buff, last);
				trigger = 1;
				break ;
			}
			i++;
		}
		if (trigger == 1)
			break ;
		line = ft_strjoin(line, buff);
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
	last = NULL;
	line = ft_readline(fd, buff, last);
	return (line);
}

int main(void)
{
	char	*line;
	int		i = 0;
	int		fd1;
	fd1 = open("test.txt", O_RDONLY);
	while (i < 3)
	{
		line = get_next_line(fd1);
		printf("%s", line);
		i++;
	}
	return (0);
}
