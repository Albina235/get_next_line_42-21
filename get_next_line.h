/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evalorie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 13:48:00 by evalorie          #+#    #+#             */
/*   Updated: 2021/10/27 15:13:05 by evalorie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *line, char *buff);
size_t    ft_strlen(char *str);
void	check_endl(char **rem, char **line);
void	ft_stc_rewrite_rem(char **rem, char *ptr);
void	ft_stc_write_line(char **line, char *buff);
void	ft_stc_last_check(int read_bite, char **line, char *last);
char	*ft_strchr(char *s, int c);
char	*ft_strdup(char *s1);
void	ft_stc_last_check(int read_bite, char **line, char *last);

#endif
