/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 00:28:14 by hyi               #+#    #+#             */
/*   Updated: 2020/12/29 15:07:57 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

char			*ft_itoa(int n)
{
	int				sign;
	int				st;
	unsigned int	div;
	unsigned int	n_u;
	char			*ret;

	sign = n < 0 ? -1 : 1;
	ft_memset(&ret, 12);
	st = 0;
	n_u = (unsigned int)(n * sign);
	while ((div = n_u / DECIMAL))
	{
		ret[st++] = n_u % DECIMAL + '0';
		n_u = div;
	}
	ret[st++] = n_u + '0';
	if (sign == -1)
		ret[st++] = '-';
	ft_str_rev(ret, st);
	return (ret);
}

int				ft_make_hex(long p, char **addr)
{
	long	div;
	long	mod;
	int		st;

	if (ft_memset(addr, HEXADECIMAL))
		return (0);
	st = 0;
	while ((div = p / HEXADECIMAL))
	{
		mod = p % HEXADECIMAL;
		*(*addr + st++) = mod < 10 ? mod + 0x30 : mod + 0x57;
		p = div;
	}
	*(*addr + st++) = p < 10 ? p + 0x30 : p + 0x57;
	return (st);
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

/*
** for processing * and atoi
*/

int				ft_get_num(t_str *str, const char *ori, int *st, int flag)
{
	int	num;

	if (ori[*st] == '*')
	{
		(*st)++;
		num = va_arg(*(str->ap), int);
	}
	else if (ori[*st] >= '0' && ori[*st] <= '9')
	{
		num = ft_atoi(&ori[*st]);
		while (ori[*st] >= '0' && ori[*st] <= '9')
			(*st)++;
	}
	else
		num = 0;
	if (flag == 1)
	{
		if ((str->width = num) < 0)
		{
			str->minus = 1;
			str->width *= -1;
		}
	}
	else
	{
		str->zero = 1;
		str->width = num;
	}
	return (-1);
}
