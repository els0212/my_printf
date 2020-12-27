/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyi <hyi@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 23:41:59 by hyi               #+#    #+#             */
/*   Updated: 2020/12/27 23:42:01 by hyi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# define HEXADECIMAL 16
# define DECIMAL 10

typedef	struct	s_str
{
	char		*content;
	int			minus;
	int			zero;
	int			width;
	int			precision;
	int			len;
}				t_str;

/*
** ft_printf_conv.c
*/
void			ft_print_string(t_str *str, va_list ap);
void			ft_print_address(t_str *str, va_list ap);
void			ft_print_digit(t_str *str, va_list ap);
void			ft_print_unsigned(t_str *str, va_list ap);
void			ft_print_hex(t_str *str, va_list ap, int flag);
/*
** ft_printf_mem_utils.c
*/
int				ft_isconv(char c, int st, int ed);
void			ft_print_char(t_str *str, va_list ap);
int				ft_memset(char **line, size_t size);
void			ft_init(char *line, size_t size);
int				ft_handle_flags(t_str *str, char **d_str, int d_len);
/*
** ft_printf_str_utils.c
*/
size_t			ft_strlen(char *s);
size_t			ft_strncat(char *dst, const char *src, size_t st, size_t ed);
void			ft_resize_and_copy(char **line, char *buf, int st, int ed);
void			ft_str_rev(char *str, int size);
void			ft_str_init(t_str *str);
/*
** ft_printf_format_utils.c
*/
long			ft_atoi(const char *nptr);
char			*ft_itoa(int n);
int				ft_make_hex(long p, char **addr);
unsigned long	ft_make_long(const char *ptr, int st, int ed);
int				ft_get_num(t_str *str, va_list ap, const char *ori, int st);
/*
** ft_printf.c
*/
int				ft_proc_conv(t_str *str, char conv, va_list ap);
int				ft_printf_loop(t_str *str, va_list ap,
		const char *ori, int *st);
int				ft_printf(const char *format, ...);
int				ft_chk_conv(t_str *str, va_list ap, const char *ori, int st);
#endif
