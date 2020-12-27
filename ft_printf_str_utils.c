/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 23:36:09 by hyi               #+#    #+#             */
/*   Updated: 2020/12/27 23:36:09 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(char *s)
{
	size_t	st;

	st = 0;
	if (!s)
		return (0);
	while (s[st])
		st++;
	return (st);
}

size_t	ft_strncat(char *dst, const char *src, size_t st, size_t ed)
{
	size_t	dst_st;

	if (!src || st == ed)
		return (-1);
	dst_st = ft_strlen(dst);
	while (src[st] && st < ed)
		dst[dst_st++] = src[st++];
	if (ed > 0)
		dst[dst_st] = '\0';
	return (dst_st);
}

void	ft_resize_and_copy(char **line, char *buf, int st, int ed)
{
	char	*temp;
	size_t	mem_size;
	size_t	line_size;

	line_size = ft_strlen(*line);
	mem_size = line_size + (ed - st) + 1;
	ft_memset(&temp, mem_size);
	ft_strncat(temp, *line, 0, line_size);
	if (*line)
		free(*line);
	ft_strncat(temp + line_size, buf, (size_t)st, (size_t)ed);
	*line = temp;
}

void	ft_str_rev(char *str, int size)
{
	int		st;
	char	temp;

	st = 0;
	while (st < size / 2)
	{
		temp = str[st];
		str[st] = str[size - st - 1];
		str[size - st - 1] = temp;
		st++;
	}
}

void	ft_str_init(t_str *str)
{
	str->content = 0;
	str->minus = -1;
	str->zero = -1;
	str->width = -1;
	str->precision = -1;
	str->len = 0;
}
