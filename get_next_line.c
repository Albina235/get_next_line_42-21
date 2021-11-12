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
#define BUFFER_SIZE 10

char	*ft_strjoin(char *line, char *buff)
{
	char	*s;
	size_t	len_line;
	size_t	len_buff;
	int		i;
	int		j;

	len_line = ft_strlen(line);
	len_buff = ft_strlen(buff);
	i = 0;
	j = 0;
	if (len_line == 0 && len_buff == 0)
		return (NULL);
	s = (char *)malloc((len_line + len_buff + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	if (line != NULL)
	{
		while (line[i] != '\0')
		{
			s[i] = line[i];
			i++;
		}
	}
	while (buff[j] != '\0')
	{
		s[i] = buff[j];
		i++;
		j++;
	}
	s[i] = '\0';
	return (s);
}

size_t    ft_strlen(const char *str)
{
    size_t    i;

    i = 0;
	if (str == NULL)
		return (0);
    while (str[i] != '\0')
        i++;
    return (i);
}

char	*ft_last(char *buff)
{
	int	i;
	int	j;
	char	*s;

	i = 0;
	j = 0;
	while (buff[i] != '\n')
		i++;
	s = (char *)malloc((BUFFER_SIZE - i) * sizeof(char));
	while (buff[++i] != '\0')
	{
		s[j] = buff[i];
		j++;
	}
	s[j] = '\0';
	printf("bi\n");
	return (s);
}

char	*ft_readline(int fd, char *buff, char *last)
{
	char	*line;
	int		i;
	int		trigger;
	char	*tmp;

	i = 0;
	tmp = NULL;
	trigger = 0;
	// line = NULL;
	line =(char *)malloc(sizeof(char) * 0);
	line = ft_strjoin(line, last);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (1)
	{
		read(fd, buff, BUFFER_SIZE);
		if (buff == NULL)
		return (NULL);
		buff[BUFFER_SIZE] = '\0';
		printf("hi, i am buff : %s\n", buff);
		while (buff[i] != '\0')
		{
			if (buff[i] == '\n')
			{
				tmp = last;
				last = ft_last(buff);
				free(tmp);
				buff[i] = '\0';
				tmp = line;
				line = ft_strjoin(line, buff);
				free(tmp);
				trigger = 1;
				break ;
			}
			i++;
		}
		if (trigger == 1 || i < BUFFER_SIZE)
			break ;
		i = 0;
		line = ft_strjoin(line, buff);
		// printf("%s", line);
	}
	free(buff);
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
	printf("hi\n");
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
		printf("%s\n", line);
		i++;
	}
	return (0);
}