/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 23:37:52 by hyi               #+#    #+#             */
/*   Updated: 2020/12/31 12:38:21 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** print %s
*/

void	ft_print_string(t_str *str)
{
	char	*s;
	char	*final_s;
	int		len;
	int		rev_flag;

	s = va_arg(*(str->ap), char *);
	if (!s)
	{
		ft_resize_and_copy(&s, "(null)", 0, 6);
	}
	len = (int)ft_strlen(s);
	final_s = 0;
	if (str->precision != -1)
		len = str->precision < len ? str->precision : len;
	ft_resize_and_copy(&final_s, s, 0, len);
	rev_flag = ft_handle_width(str, &final_s, len, 0);
	ft_write_conv(str, final_s, rev_flag);
}

/*
** print %p
*/

void	ft_print_address(t_str *str)
{
	char	*p;
	char	*addr;
	int		rev_flag;
	int		addr_len;

	p = va_arg(*(str->ap), char *);
	ft_make_hex((long)p, &addr);
	if (!p && !str->precision)
		*addr = '\0';
	ft_resize_and_copy(&addr, "x0", 0, 2);
	addr_len = ft_strlen(addr);
	ft_str_rev(addr, addr_len);
	rev_flag = ft_handle_width(str, &addr, addr_len, 0);
	ft_write_conv(str, addr, rev_flag);
}

/*
** print %d, %i
*/

void	ft_print_digit(t_str *str)
{
	int		d;
	char	*d_str;
	int		d_len;
	int		rev_flag;

	d = va_arg(*(str->ap), int);
	str->sign = d < 0 ? '-' : 0;
	d_str = ft_itoa(d);
	if (!d && !str->precision)
		*d_str = '\0';
	d_len = (int)ft_strlen(d_str);
	rev_flag = ft_handle_prec(str, &d_str, &d_len);
	rev_flag = ft_handle_width(str, &d_str, d_len, rev_flag);
	ft_write_conv(str, d_str, rev_flag);
}

/*
** print %u
*/

void	ft_print_unsigned(t_str *str)
{
	unsigned int	n;
	unsigned int	div;
	char			*d_str;
	int				st;
	int				rev_flag;

	n = va_arg(*(str->ap), unsigned int);
	ft_memset(&d_str, 12);
	st = 0;
	while ((div = n / DECIMAL))
	{
		d_str[st++] = n % DECIMAL + '0';
		n = div;
	}
	d_str[st++] = n + '0';
	if (!n && !str->precision)
	{
		*d_str = '\0';
		st = 0;
	}
	ft_str_rev(d_str, st);
	rev_flag = ft_handle_prec(str, &d_str, &st);
	rev_flag = ft_handle_width(str, &d_str, st, rev_flag);
	ft_write_conv(str, d_str, rev_flag);
}

/*
** print %x, %X
*/

void	ft_print_hex(t_str *str, int flag)
{
	unsigned int	n;
	char			*d_str;
	int				d_len;
	int				st;
	int				rev_flag;

	n = va_arg(*(str->ap), unsigned int);
	d_len = ft_make_hex((long)n, &d_str);
	ft_str_rev(d_str, d_len);
	if (!n && !str->precision)
		*d_str = '\0';
	if (flag == 1)
	{
		st = 0;
		while (st < d_len)
		{
			if (d_str[st] >= 'a' && d_str[st] <= 'z')
				d_str[st] -= 0x20;
			st++;
		}
	}
	d_len = ft_strlen(d_str);
	rev_flag = ft_handle_prec(str, &d_str, &d_len);
	rev_flag = ft_handle_width(str, &d_str, d_len, rev_flag);
	ft_write_conv(str, d_str, rev_flag);
}
