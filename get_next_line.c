/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:48:03 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/23 14:48:04 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t len)
{
	size_t	i;

	if (len == 0 || dst == src)
		return (dst);
	i = 0;
	while (i < len)
	{
		((unsigned char *) dst)[i] = ((unsigned char *) src)[i];
		i++;
	}
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if ((int) *s == c)
			return ((char *) s);
		s++;
	}
	if ((int) *s == c)
		return ((char *) s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = 0;
	s2_len = 0;
	if (s1)
		s1_len = ft_strlen(s1);
	if (s2)
		s2_len = ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (s1_len + s2_len) + 1);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, s1_len);
	ft_memcpy(ptr + s1_len, s2, s2_len);
	*(ptr + (s1_len + s2_len)) = '\0';
	return (ptr);
}

static char	*_read_str(int fd, char *str)
{
	char	*buf;
	size_t	read_bytes;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (!ft_strchr(str, '\n'))
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(buf);
			return (NULL);
		}
		*(buf + read_bytes) = '\0';
		str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

int	get_next_line(int fd, char **line)
{
	static char	*line_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	line_str = _read_line(fd, line_str);
}


int	main(void)
{
	int		fd;
	char	**line;

	fd = open("test1", O_RDONLY);
	get_next_line(fd, line);
}
