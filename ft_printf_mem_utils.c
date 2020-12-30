/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_mem_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 23:40:18 by hyi               #+#    #+#             */
/*   Updated: 2020/12/30 23:53:22 by hyi              ###   ########.fr       */
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
