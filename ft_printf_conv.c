/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 23:37:52 by hyi               #+#    #+#             */
/*   Updated: 2020/12/30 23:40:58 by hyi              ###   ########.fr       */
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
	//free(s);
	rev_flag = ft_handle_width(str, &final_s, len, 0);
	ft_write_conv(str, final_s, rev_flag);
	/*
	len = ft_strlen(final_s);
	if (rev_flag)
		ft_str_rev(final_s, len);
	str->len += len;
	write(1, final_s, len);
	free(final_s);
	*/
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
	ft_resize_and_copy(&addr, "x0", 0, 2);
	addr_len = ft_strlen(addr);
	ft_str_rev(addr, addr_len);
	rev_flag = ft_handle_width(str, &addr, addr_len, 0);
	ft_write_conv(str, addr, rev_flag);
	/*
	addr_len = ft_strlen(addr);
	if (rev_flag)
		ft_str_rev(addr, addr_len);
	str->len += addr_len;
	write(1, addr, addr_len);
	free(addr);
	*/
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
	/*
	rev_flag = ft_handle_flags(str, &d_str, d_len);
	d_len = ft_strlen(d_str);
	d_str[d_len] = '\0';
	if (rev_flag)
		ft_str_rev(d_str, d_len);
	str->len += d_len;
	write(1, d_str, d_len);
	free(d_str);
	*/
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
	/*
	rev_flag = ft_handle_flags(str, &d_str, st);
	st = ft_strlen(d_str);
	d_str[st] = '\0';
	if (rev_flag)
		ft_str_rev(d_str, st);
	str->len += st;
	write(1, d_str, st);
	free(d_str);
	*/
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
	rev_flag = ft_handle_prec(str, &d_str, &d_len);
	rev_flag = ft_handle_width(str, &d_str, d_len, rev_flag);
	ft_write_conv(str, d_str, rev_flag);
	/*
	rev_flag = ft_handle_flags(str, &d_str, (int)ft_strlen(d_str));
	d_len = ft_strlen(d_str);
	d_str[d_len] = '\0';
	if (rev_flag)
		ft_str_rev(d_str, d_len);
	str->len += d_len;
	write(1, d_str, d_len);
	free(d_str);
	*/
}
