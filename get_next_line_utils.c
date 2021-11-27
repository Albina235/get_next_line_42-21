/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evalorie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:34:19 by evalorie          #+#    #+#             */
/*   Updated: 2021/11/24 15:07:06 by evalorie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	size_t	n;
	int		i;

	n = ft_strlen(s1);
	i = 0;
	if (ft_strlen(s1) == 0)
		return (NULL);
	s2 = (char *)malloc((n + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

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
	return (mem);
}

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
