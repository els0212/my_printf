/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 23:40:02 by hyi               #+#    #+#             */
/*   Updated: 2020/12/31 15:37:23 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** for format string conversion
*/

int	ft_proc_conv(t_str *str, char conv)
{
	if (!ft_isconv(conv, 0, 9))
		return (-1);
	if (conv == 'c')
		ft_print_char(str);
	else if (conv == 's')
		ft_print_string(str);
	else if (conv == 'p')
		ft_print_address(str);
	else if (conv == 'd')
		ft_print_digit(str);
	else if (conv == 'i')
		ft_print_digit(str);
	else if (conv == 'u')
		ft_print_unsigned(str);
	else if (conv == 'x')
		ft_print_hex(str, 0);
	else if (conv == 'X')
		ft_print_hex(str, 1);
	else if (conv == '%')
		ft_print_percent(str);
	return (0);
}

int	ft_chk_conv(t_str *str, const char *ori, int st)
{
	while (1)
	{
		if (ori[st] == '-')
			str->minus = 1;
		else if (ori[st] == '0')
			str->zero = 1;
		else
			break ;
		st++;
	}
	ft_get_num(str, ori, &st, 1);
	if (ori[st] == '.')
	{
		st++;
		ft_get_num(str, ori, &st, 2);
	}
	if (ft_proc_conv(str, ori[st]) == -1)
		return (-1);
	st++;
	return (st);
}

int	ft_printf_loop(t_str *str, const char *ori, int *st)
{
	int	sub_st;

	sub_st = *st;
	ft_str_init(str, str->len);
	while (ori[sub_st] && ori[sub_st] != '%')
		sub_st++;
	write(1, &ori[*st], sub_st - *st);
	str->len += (sub_st - *st);
	if (!ori[*st = sub_st])
		return (1);
	(*st)++;
	if ((*st = ft_chk_conv(str, ori, *st)) == -1)
		return (-1);
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
	ft_str_init(&str, 0);
	str.ap = &ap;
	while (ori[st])
		if (ft_printf_loop(&str, ori, &st))
			break ;
	va_end(ap);
	return (str.len);
}
