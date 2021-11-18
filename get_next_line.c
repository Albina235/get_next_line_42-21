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

char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *line, char *buff);
size_t    ft_strlen(char *str);
void	check_endl(char *rem, char *line);
static char	*ft_stc_rewrite_last(char *last, char *ptr);
static char	*ft_stc_write_line(char *line, char *buff);
//static void	ft_stc_last_check(int read_bite, char *line, char *last);


char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

/*char	*ft_strjoin(char *line, char *buff)
{
	char	*s;
	size_t	len_line;
	size_t	len_buff;
	int		i;

	if (!buff)
		return (NULL);
	len_line = ft_strlen(line);
	len_buff = ft_strlen(buff);
	//if (len_line == 0 && len_buff == 0)
	//	return (NULL);
	s = (char *)malloc((len_line + len_buff + 1) * sizeof(char));

	i = -1;
	while (line[++i])
		s[i] = line[i];
	i = -1;
	while (buff[++i])
	{
		s[len_line] = buff[i];
		len_line++;
	}
	s[len_line] = '\0';
	return (s);
}*/

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*mem;

	i = 0;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	mem = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (mem == NULL)
		return (NULL);
	while (s1 && s1[i])
		mem[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i])
		mem[j++] = s2[i++];
	mem[j] = '\0';
	free (s1);
	return (mem);
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	size_t	n;
	int		i;
	
	n = ft_strlen(s1);
	s2 = (char *)malloc((n + 1)* sizeof(char));
	if (s2 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	/*if (s1[i] == '\n')
	{
		s1[i] = '\n';
		i++;
	}*/
	s2[i] = '\0';
	return (s2);
}

size_t    ft_strlen(char *str)
{
    size_t    i;

    i = 0;
	if (!str)
		return (0);
    while (str[i] != '\0')
        i++;
    return (i);
}

void	check_endl(char *rem, char *line)
{
	char	*c;
	char	*tmp;
	int		k;

	c = NULL;
	if (rem)
	{
		c = ft_strchr(rem, '\n');
		if (c)
		{
			tmp = rem;
			rem = ft_strdup(++c);
			c[1] = '\0';
			line = ft_strdup(tmp);
			free(tmp);
		}
		else
		{
			line = ft_strdup(rem);
			free(rem);
			rem = NULL;
		}
	}
}

static char	*ft_stc_rewrite_rem(char *last, char *ptr)
{
	if (last != 0)
		free(last);
	last = NULL;
	last = ft_strdup(ptr + 1);
	return (last);
}

static char	*ft_stc_write_line(char *line, char *buff)
{
	char	*tmp;

	if (line != NULL)
		tmp = line;
	line = ft_strjoin(line, buff);
	if (tmp != NULL)
		free(tmp);
	return (line);
}

/*static void	ft_stc_last_check(int read_bite, char *line, char *last)
{
	if (read_bite || ft_strlen(last) || ft_strlen(line))
		return ;
	else
	{
		free(line);
		line = NULL;
	}

}*/

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	static char	*rem[256];
	char		*line;
	char		*ptr;
	int			read_bite;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0 , 0) < 0)
		return (NULL);
	line = NULL;
	check_endl(rem[fd], line);
	read_bite = 1;
	while (!ft_strchr(line, '\n') || (!line && read_bite))
	{
		read_bite = read(fd, buff, BUFFER_SIZE);
		buff[BUFFER_SIZE] = '\0';
		ptr = ft_strchr(buff, '\n');
		if (ptr)
		{
			rem[fd] = ft_stc_rewrite_rem(rem[fd], ptr);
			ptr[1] = '\0';
		}
		line = ft_stc_write_line(line, buff);
	}
	//ft_stc_last_check(read_bite, line, rem[fd]);
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
	close(fd1);
	return (0);
}