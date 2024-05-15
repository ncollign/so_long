/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembou      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:30:06 by ncollign          #+#    #+#             */
/*   Updated: 2024/04/25 18:33:33 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	check_type(va_list args, const char format)
{
	int	length;

	length = 0;
	if (format == 'c')
		length += ft_putchar(va_arg(args, int));
	else if (format == 's')
		length += ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		length += ft_putptr(va_arg(args, unsigned long int));
	else if (format == 'd' || format == 'i')
		length += ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		length += ft_putunbr(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		length += ft_puthex(va_arg(args, unsigned long int), format);
	else if (format == '%')
		length += ft_putchar('%');
	return (length);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	size_t	length;

	va_start(args, str);
	i = 0;
	length = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			if (ft_strchr("cspdiuxX\%", str[i]))
				length += check_type(args, str[i]);
		}
		else
			length += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (length);
}
