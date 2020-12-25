#include "ft_printf.h"

int	ft_isconv(char c, int st, int ed)
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

int	ft_printf(const char *ori, ...)
{
	va_list	ap;
	int		ret;
	int		st;
	int		sub_st;
	char	*str;
	int		width;
	int		precision;

	if (!ori)
		return (-1);
	va_start(ap, ori);
	ret = 0;
	st = 0;
	str = 0;
	width = -1;
	precision = -1;
	while (ori[st])
	{
		sub_st = st;
		while (ori[sub_st] && ori[sub_st] != '%')
			sub_st++;
		ft_resize_and_copy(&str, (char *)ori, st, sub_st);
		//printf("1st str = %s\n", str);
		if (!ori[st = sub_st]) 
			break ;
		st++;
		/*
		if (!ft_isconv(ori[st], 0, 13))
		{
			printf("free!\n");
			if (str)
				free(str);
			return (-1);
		}
		*/
		if (ori[st] == '%')
		{
			printf("%%%%!!\n");
			ft_resize_and_copy(&str, (char *)ori, st, st + 1);
			st++;
		}
		else
		{
			printf("in %%, st = %d\n", st);
			/*
			while (ori[sub_st] && ft_isconv(ori[sub_st], 9, 13))
				sub_st++;
			
			if (!ori[sub_st] || !ft_isconv(ori[sub_st], 0, 9))
			{
				printf("fail!\n");
				if (str)
					free(str);
				return (-1);
			}
			*/
			if (ori[st] == '-')
			{
				sub_st++;
				if (ori[st] == '0')
					st++;
				if (ori[st] == '*')
				{
					width = va_arg(ap, int);
					st++;
				}
				else if (ori[st] >= '0' && ori[st] <= '9')
				{
						width = (int)ft_atoi(&ori[st]);
						while (ori[st] >= '0' && ori[st] <= '9')
							st++;
				}
			}
			if (ori[st] >= '0' && ori[st] <= '9')
			{
				//printf("ori[st] = %c\n", ori[st]);
				width = (int)ft_atoi(&ori[st]);
				while (ori[st] >= '0' && ori[st] <= '9')
					st++;
			}
			else if (ori[st] == '*')
			{
				width = va_arg(ap, int);
				st++;
			}
			if (ori[st] == '.')
			{
					st++;
				if (ori[st] == '*')
				{
					precision = va_arg(ap, int);
					st++;
				}
				else if (ori[st] >= '0' && ori[st] <= '9')
				{
					precision = (int)ft_atoi(&ori[st]);
					while (ori[st] >= '0' && ori[st] <= '9')
						st++;
				}
			}

			printf("prec = %d, width = %d\n", precision, width);
			st++;
		}
		//printf("st = %d, sub_st = %d, str = %s\n", st ,sub_st, str);
	}
	ret = ft_strlen(str);
	write(1, str, ret);
	free(str);
	va_end(ap);
	return (ret);
}

int main(void)
{
	//printf("printf : %-60.d\n", 3 );
	ft_printf("abcd.%3.d");
	return 0;
}
