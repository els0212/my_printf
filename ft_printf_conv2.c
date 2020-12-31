/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_conv2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 23:53:42 by hyi               #+#    #+#             */
/*   Updated: 2020/12/31 13:03:40 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** print %c
*/

int		ft_print_percent(t_str *str)
{
	char	*c_str;
	int		rev_flag;
	int		c_len;

	ft_resize_and_copy(&c_str, "%", 0, 1);
	rev_flag = ft_handle_width(str, &c_str, 1, 0);
	c_len = (int)ft_strlen(c_str);
	if (rev_flag)
		ft_str_rev(c_str, c_len);
	str->len += c_len;
	write(1, c_str, c_len);
	free(c_str);
	return (c_len);
}

/*
** print %c
*/

void	ft_print_char(t_str *str)
{
	char	c;
	char	*c_str;
	int		c_len;
	int		rev_flag;

	c = va_arg(*(str->ap), int);
	c_str = 0;
	ft_resize_and_copy(&c_str, &c, 0, 1);
	rev_flag = ft_handle_width(str, &c_str, 1, 0);
	c_len = !c ? ft_strlen(c_str) + 1 : ft_strlen(c_str);
	if ((!c && !rev_flag) || (c && rev_flag))
		ft_str_rev(c_str, c_len);
	str->len += c_len;
	write(1, c_str, c_len);
	free(c_str);
}

int		ft_handle_prec(t_str *str, char **d_str, int *d_len)
{
	int	len;
	int	rev_flag;

	rev_flag = 0;
	len = str->sign == '-' ? *d_len - 1 : *d_len;
	if (str->precision > len)
	{
		ft_str_rev(*d_str, *d_len);
		rev_flag++;
		if (str->sign == '-')
			*(*d_str + (--(*d_len))) = '\0';
		while (*d_len < str->precision)
		{
			ft_resize_and_copy(d_str, "0", 0, 1);
			(*d_len)++;
		}
		if (str->sign == '-')
			*(*d_str + ((*d_len)++)) = str->sign;
		*(*d_str + *d_len) = '\0';
	}
	return (rev_flag);
}

int		ft_handle_width(t_str *str, char **d_str, int d_len, int rev_flag)
{
	int		sign_idx;
	char	c;

	c = (str->zero == 1 && str->minus != 1 && str->precision == -1) ? '0' : ' ';
	if (str->width > d_len)
	{
		if ((!rev_flag && str->minus == -1) || (rev_flag && str->minus != -1))
		{
			ft_str_rev(*d_str, d_len);
			rev_flag = !rev_flag ? rev_flag + 1 : 0;
		}
		sign_idx = d_len - 1;
		while (d_len++ < str->width)
			ft_resize_and_copy(d_str, &c, 0, 1);
		if (str->sign == '-' && str->zero == 1 &&
				str->minus == -1 && str->precision == -1)
		{
			*(*d_str + sign_idx) = '0';
			*(*d_str + d_len - 2) = '-';
		}
		*(*d_str + d_len - 1) = '\0';
	}
	return (rev_flag);
}

void	ft_write_conv(t_str *str, char *d_str, int rev_flag)
{
	int	len;

	len = ft_strlen(d_str);
	d_str[len] = '\0';
	if (rev_flag)
		ft_str_rev(d_str, len);
	str->len += len;
	write(1, d_str, len);
	free(d_str);
	d_str = 0;
}
