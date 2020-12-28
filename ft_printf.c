/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 23:40:02 by hyi               #+#    #+#             */
/*   Updated: 2020/12/28 16:48:06 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** for format string conversion
*/

int	ft_proc_conv(t_str *str, char conv, va_list ap)
{
	if (!ft_isconv(conv, 0, 8))
		return (-1);
	if (conv == 'c')
		ft_print_char(str, ap);
	else if (conv == 's')
		ft_print_string(str, ap);
	else if (conv == 'p')
		ft_print_address(str, ap);
	else if (conv == 'd')
		ft_print_digit(str, ap);
	else if (conv == 'i')
		ft_print_digit(str, ap);
	else if (conv == 'u')
		ft_print_unsigned(str, ap);
	else if (conv == 'x')
		ft_print_hex(str, ap, 0);
	else if (conv == 'X')
		ft_print_hex(str, ap, 1);
	return (0);
}

int	ft_chk_conv(t_str *str, va_list ap, const char *ori, int st)
{
	int	ed;

	ed = st + 2;
	while (st != ed)
	{
		str->minus = ori[st] == '-' ? 1 : -1;
		str->zero = ori[st] == '0' ? 1 : -1;
		if (str->minus == str->zero)
			break ;
		st++;
	}
	if ((str->width = ft_get_num(ap, ori, &st)) < 0)
	{
		str->minus = 1;
		str->width *= -1;
	}
	if (ori[st] == '.')
	{
		st++;
		str->precision = ft_get_num(ap, ori, &st);
	}
	if (ft_proc_conv(str, ori[st], ap) == -1)
		return (-1);
	st++;
	return (st);
}

int	ft_printf_loop(t_str *str, va_list ap, const char *ori, int *st)
{
	int	sub_st;

	sub_st = *st;
	while (ori[sub_st] && ori[sub_st] != '%')
		sub_st++;
	ft_resize_and_copy(&(str->content), (char *)ori, *st, sub_st);
	if (!ori[*st = sub_st])
		return (1);
	(*st)++;
	if (ori[*st] == '%')
	{
		ft_resize_and_copy(&(str->content), (char *)ori, *st, *st + 1);
		(*st)++;
	}
	else
	{
		if ((*st = ft_chk_conv(str, ap, ori, *st)) == -1)
			return (-1);
	}
	return (0);
}

int	ft_printf(const char *ori, ...)
{
	va_list	ap;
	int		st;
	t_str	str;

	if (!ori)
		return (-1);
	va_start(ap, ori);
	st = 0;
	ft_str_init(&str);
	while (ori[st])
		if (ft_printf_loop(&str, ap, ori, &st))
			break ;
	str.len = ft_strlen(str.content);
	write(1, str.content, str.len);
	free(str.content);
	va_end(ap);
	return (str.len);
}
