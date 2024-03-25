/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzouk <amarzouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:08:17 by amarzouk          #+#    #+#             */
/*   Updated: 2024/01/22 09:02:31 by amarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printf_checker(char c, va_list *args, int *len, int *i)
{
	if (c == 's')
		ft_string(va_arg(*args, char *), len);
	else if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(*args, int), len);
	else if (c == 'u')
		ft_unsigned_int(va_arg(*args, unsigned int), len);
	else if (c == 'x' || c == 'X')
		ft_hexa(va_arg(*args, unsigned int), len, c);
	else if (c == 'p')
		ft_pointer(va_arg(*args, unsigned long), len);
	else if (c == 'c')
		ft_ch(va_arg(*args, int), len);
	else if (c == '%')
		ft_ch('%', len);
	else
		(*i)--;
}

void	ft_ch(char c, int *len)
{
	write(1, &c, 1);
	(*len)++;
}

void	ft_string(char *s, int *len)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		(*len) = (*len) + 6;
		return ;
	}
	while (s[i] != '\0')
	{
		ft_ch(s[i], len);
		i++;
	}
}

int	ft_printf(const char *s, ...)
{
	int		i;
	int		length;
	va_list	args;

	i = 0;
	length = 0;
	if (!s)
		return (0);
	va_start(args, s);
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			i++;
			ft_printf_checker(s[i], &args, &length, &i);
			i++;
		}
		else
		{
			ft_ch((char)s[i], &length);
			i++;
		}
	}
	va_end(args);
	return (length);
}
