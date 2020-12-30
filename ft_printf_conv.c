/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 23:37:52 by hyi               #+#    #+#             */
/*   Updated: 2020/12/30 19:18:48 by hyi              ###   ########.fr       */
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
	len = (int)ft_strlen(s);
	final_s = 0;
	if (str->precision != -1)
		len = str->precision < len ? str->precision : len;
	ft_resize_and_copy(&final_s, s, 0, len);
	rev_flag = ft_handle_width(str, &final_s, len, 0);
	len = ft_strlen(final_s);
	if (rev_flag)
		ft_str_rev(final_s, len);
	//printf("rev_flag = %d, prec = %d, s = %s, len = %d\n",rev_flag, str->precision, final_s, len);
	ft_resize_and_copy(&(str->content), final_s, 0, len);
}

/*
** print %p
*/

void	ft_print_address(t_str *str)
{
	char	*p;
	char	*addr;

	p = va_arg(*(str->ap), char *);
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
	rev_flag = ft_handle_flags(str, &d_str, (int)ft_strlen(d_str));
	d_len = ft_strlen(d_str);
	d_str[d_len] = '\0';
	if (rev_flag)
		ft_str_rev(d_str, d_len);
	ft_resize_and_copy(&(str->content), d_str, 0, d_len);
	free(d_str);
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
	printf("n = %ld\n",n);
	ft_memset(&d_str, 12);
	st = 0;
	while ((div = n / DECIMAL))
	{
		d_str[st++] = n % DECIMAL + '0';
		n = div;
	}
	d_str[st++] = n + '0';
	/*
	ft_str_rev(d_str, st);
	if (ft_handle_flags(str, &d_str, st) > 1)
		ft_str_rev(d_str, st = ft_strlen(d_str));
	*/
	ft_str_rev(d_str, st);
	rev_flag = ft_handle_flags(str, &d_str, st);
	printf("rev_flag = %d, str = %s\n",rev_flag, d_str);
	st = ft_strlen(d_str);
	d_str[st] = '\0';
	if (rev_flag)
		ft_str_rev(d_str, st);
	ft_resize_and_copy(&(str->content), d_str, 0, st);
	free(d_str);
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

	n = va_arg(*(str->ap), unsigned int);
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
