/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:48:11 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/23 14:48:11 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
#include <fcntl.h>
# define BUFFER_SIZE 10

char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);

int		get_next_line(int fd, char **line);
#endif
