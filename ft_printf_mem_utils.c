/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_mem_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 23:40:18 by hyi               #+#    #+#             */
/*   Updated: 2020/12/28 21:18:31 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_isconv(char c, int st, int ed)
{
	char	*s;

	s = "cspdiuxX%0*.-";
	st = st < 0 ? 0 : st;
	while (s[st] && st < ed)
	{
		if (s[st] == c)
			return (1);
		st++;
	}
	return (0);
}

/*
** print %c
*/

void	ft_print_char(t_str *str)
{
	char	c;

	c = va_arg(*(str->ap), int);
	ft_resize_and_copy(&(str->content), &c, 0, 1);
}

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

int		ft_handle_flags(t_str *str, char **d_str, int d_len)
{
	char	c;

	if (str->minus != -1)
	{
		while (d_len++ < str->width)
			ft_resize_and_copy(d_str, " ", 0, 1);
		return (1);
	}
	if (str->width > d_len)
	{
		ft_str_rev(*d_str, d_len);
		c = str->zero == -1 ? ' ' : '0';
		while (d_len++ < str->width)
			ft_resize_and_copy(d_str, &c, 0, 1);
		return (c);
	}
	return (0);
}
