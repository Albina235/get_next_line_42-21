/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evalorie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:37:45 by evalorie          #+#    #+#             */
/*   Updated: 2021/11/24 15:39:23 by evalorie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	void	check_endl(char **rem, char **line)
{
	char	*c;
	char	*tmp;

	c = NULL;
	tmp = *rem;
	if (*rem)
	{
		c = ft_strchr(*rem, '\n');
		if (c)
		{
			*rem = ft_strdup(++c);
			c[0] = '\0';
			*line = ft_strdup(tmp);
			free(tmp);
		}
		else
		{
			*line = ft_strdup(*rem);
			free(*rem);
			*rem = NULL;
		}
	}
}

static	void	ft_stc_rewrite_rem(char **rem, char *ptr)
{
	if (*ptr != '\0')
	{
		if (*rem != 0)
		{
			free(*rem);
			*rem = NULL;
		}	
		*rem = ft_strdup(ptr);
	}
}

static	void	ft_stc_write_line(char **line, char *buff)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buff);
	if (tmp != 0)
		free(tmp);
}

static	void	ft_dop(char **rem, char *ptr)
{
	ft_stc_rewrite_rem(rem, ++ptr);
	ptr[0] = '\0';
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	static char	*rem;
	char		*line;
	char		*ptr;
	int			read_byte;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = NULL;
	check_endl(&rem, &line);
	read_byte = 1;
	while (!ft_strchr(line, '\n') || (!line && read_byte))
	{
		read_byte = read(fd, buff, BUFFER_SIZE);
		if (read_byte == 0)
			return (line);
		buff[read_byte] = '\0';
		ptr = ft_strchr(buff, '\n');
		if (ptr)
			ft_dop(&rem, ptr);
		ft_stc_write_line(&line, buff);
	}
	return (line);
}

/*int main(void)
{
	char	*line;
	//int		i = 0;
	int		fd1;
	fd1 = open("test.txt", O_RDONLY);
	// while (i < 5)
	// {
	// 	line = get_next_line(fd1);
	// 	printf("%s\n", line);
	// 	i++;
	// }
	//printf("%s\n", "works");
	line = get_next_line(fd1);
	printf("s = %s", line);
	free(line);
	line = get_next_line(fd1);
	printf("s = %s", line);
	free(line);
	line = get_next_line(fd1);
	printf("s = %s", line);
	free(line);
	line = get_next_line(fd1);
	printf("s = %s", line);
	free(line);
	line = get_next_line(fd1);
	printf("s = %s", line);
	free(line);
	line = get_next_line(fd1);
	printf("s = %s", line);
	free(line);
	line = get_next_line(fd1);
	printf("s = %s", line);
	free(line);
	close(fd1);
	return (0);
}*/
