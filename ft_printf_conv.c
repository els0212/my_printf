/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 23:37:52 by hyi               #+#    #+#             */
/*   Updated: 2020/12/28 11:52:42 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** print %s
*/

void	ft_print_string(t_str *str, va_list ap)
{
	char	*s;
	size_t	len;

	s = va_arg(ap, char *);
	len = ft_strlen(s);
	ft_resize_and_copy(&(str->content), s, 0, len);
	free(s);
}

/*
** print %p
*/

void	ft_print_address(t_str *str, va_list ap)
{
	char	*p;
	char	*addr;

	p = va_arg(ap, char *);
	if (!p)
	{
		ft_memset(&addr, 5);
		ft_strncat(addr, "(nil)", 0, 5);
	}
	else
	{
		ft_make_hex((long)p, &addr);
		ft_resize_and_copy(&addr, "x0", 0, 2);
		ft_str_rev(addr, ft_strlen(addr));
	}
	ft_resize_and_copy(&(str->content), addr, 0, ft_strlen(addr));
	free(addr);
}

/*
** print %d, %i
*/

void	ft_print_digit(t_str *str, va_list ap)
{
	int		d;
	char	*d_str;
	int		d_len;
	int		flag;

	d = va_arg(ap, int);
	if (!d && !str->precision)
		return ;
	d_str = ft_itoa(d);
	d_len = (int)ft_strlen(d_str);
	
	if ((flag = ft_handle_flags(str, &d_str, d_len)))
	{
		if (flag == '0' && d < 0)
			d_str[d_len - 1] = '0';
		d_len = ft_strlen(d_str);
		if (flag > 1)
			ft_str_rev(d_str, d_len);
		if (flag == '0' && d < 0)
			d_str[0] = '-';
	}
	ft_resize_and_copy(&(str->content), d_str, 0, d_len);
	free(d_str);
}

/*
** print %u
*/

void	ft_print_unsigned(t_str *str, va_list ap)
{
	unsigned int	n;
	unsigned int	div;
	char			*d_str;
	int				st;

	n = va_arg(ap, unsigned int);
	ft_memset(&d_str, 12);
	st = 0;
	while ((div = n / DECIMAL))
	{
		d_str[st++] = n % DECIMAL + '0';
		n = div;
	}
	d_str[st++] = n + '0';
	ft_str_rev(d_str, st);
	if (ft_handle_flags(str, &d_str, st) > 1)
		ft_str_rev(d_str, st = ft_strlen(d_str));
	ft_resize_and_copy(&(str->content), d_str, 0, st);
	free(d_str);
}

/*
** print %x, %X
*/

void	ft_print_hex(t_str *str, va_list ap, int flag)
{
	unsigned int	n;
	char			*d_str;
	int				d_len;
	int				st;

	n = va_arg(ap, unsigned int);
	d_len = ft_make_hex((long)n, &d_str);
	ft_str_rev(d_str, d_len);
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
	ft_resize_and_copy(&(str->content), d_str, 0, d_len);
	free(d_str);
}
