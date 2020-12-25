/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 00:28:14 by hyi               #+#    #+#             */
/*   Updated: 2020/12/25 23:07:09 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_memset(char **line, size_t size)
{
	if (!(*line = (char *)malloc(sizeof(char) * (size + 1))))
		return (-1);
	ft_init(*line, size);
	return (0);
}

void	ft_init(char *line, size_t size)
{
	size_t	st;

	st = 0;
	while (st < size)
		*(line + st++) = 0;
}

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

unsigned long	ft_make_long(const char *ptr, int st, int ed)
{
	unsigned long	ret;
	unsigned long	mod;

	ret = 0;
	mod = 1;
	while (--ed >= st)
	{
		ret += ((unsigned long)(ptr[ed] - '0') * mod);
		mod *= 10;
	}
	return (ret);
}

long			ft_atoi(const char *nptr)
{
	int		st;
	int		ed;
	long	sign;

	sign = 1;
	st = 0;
	while (nptr[st] && (nptr[st] == ' ' ||
				(nptr[st] >= 0x09 && nptr[st] <= 0x0D)))
		st++;
	if (!nptr[st])
		return (0);
	if (nptr[st] == '-')
		sign = -1;
	if (sign == -1 || nptr[st] == '+')
		st++;
	if (nptr[st] < '0' || nptr[st] > '9')
		return (0);
	ed = st;
	while (nptr[ed] >= '0' && nptr[ed] <= '9')
		ed++;
	return (ft_make_long(nptr, st, ed) * sign);
}
