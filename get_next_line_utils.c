/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:47:52 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/25 23:23:59 by lyeh             ###   ########.fr       */
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

void	*ft_memcpy(void *dst, const void *src, size_t len)
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
	while (s && *s)
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

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	src_len;

	src_len = ft_strlen(s1);
	dst = (char *)malloc(sizeof(char) * src_len + 1);
	if (dst == NULL)
		return (NULL);
	ft_memcpy(dst, s1, src_len + 1);
	return (dst);
}
