/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembou      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:43:44 by ncollign          #+#    #+#             */
/*   Updated: 2024/04/25 18:48:09 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_itoa_hex(unsigned long n, const char format)
{
	const char	*hex_digits;
	int			nb_length;

	if (format == 'X')
		hex_digits = "ABCDEF";
	else
		hex_digits = "abcdef";
	nb_length = 0;
	if (n == 0)
		nb_length += ft_putchar('0');
	else if (n >= 16)
	{
		nb_length += ft_itoa_hex(n / 16, format);
		nb_length += ft_itoa_hex(n % 16, format);
	}
	else
	{
		if (n <= 9)
			nb_length += ft_putchar(n + '0');
		else
			nb_length += ft_putchar(hex_digits[n - 10]);
	}
	return (nb_length);
}
