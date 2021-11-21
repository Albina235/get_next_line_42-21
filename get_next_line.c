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
//#define BUFFER_SIZE

void	check_endl(char **rem, char **line)
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
			//tmp = *rem;
			*rem = ft_strdup(++c);
			c[1] = '\0';
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

void	ft_stc_rewrite_rem(char **rem, char *ptr)
{
	//printf("c\n");
	if (*ptr != '\0')
	{
		if (*rem != 0)
		{
			free(*rem);
			*rem = NULL;
		}	
		*rem = ft_strdup(ptr);
	}
	//printf("c\n");
}

void	ft_stc_write_line(char **line, char *buff)
{
	char	*tmp;

	tmp = *line;
	/*if (line != NULL)
		tmp = line;*/
	*line = ft_strjoin(*line, buff);
	if (tmp != 0)
		free(tmp);
	//return (line);
}

void	ft_stc_last_check(int read_bite, char **line, char *last)
{
	/*if (read_bite || ft_strlen(last))
		ft_stc_write_line(line, "\n");*/
	if (read_bite || ft_strlen(last) || ft_strlen(*line))
		return ;
	else
	{
		free(*line);
		*line = 0;
	}

}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	static char	*rem;
	char		*line;
	char		*ptr;
	int			read_bite;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0 , 0) < 0)
		return (NULL);
	line = NULL;
	buff[0] = 0;
	check_endl(&rem, &line);
	read_bite = 1;
	while (!ft_strchr(line, '\n') || (!line && read_bite))
	{
		read_bite = read(fd, buff, BUFFER_SIZE);
		buff[read_bite] = '\0';
		//printf("%d  %s\n", read_bite, buff);
		if (read_bite == 0)
			return (line);
		ptr = ft_strchr(buff, '\n');
		if (ptr)
		{
			ft_stc_rewrite_rem(&rem, ++ptr);
			ptr[0] = '\0';
		}
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
	line = get_next_line(fd1);
	printf("s = %s", line);
	close(fd1);
	return (0);
}*/