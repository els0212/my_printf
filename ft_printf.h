#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
#include <stdio.h>

int		ft_printf(const char *format, ...);
int		ft_memset(char **line, size_t size);
void	ft_init(char *line, size_t size);
size_t	ft_strlen(char *s);
size_t	ft_strncat(char *dst, const char *src, size_t st, size_t ed);
void	ft_resize_and_copy(char **line, char *buf, int st, int ed);
unsigned long	ft_make_long(const char *ptr, int st, int ed);
long			ft_atoi(const char *nptr);
#endif
