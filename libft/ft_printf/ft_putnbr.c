/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembou      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:39:04 by ncollign          #+#    #+#             */
/*   Updated: 2024/04/25 18:40:40 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putnbr(int n)
{
	int	nb_length;

	nb_length = 0;
	if (n == -2147483648)
		nb_length = ft_putstr("-2147483648");
	else if (n < 0)
	{
		nb_length += ft_putchar('-');
		nb_length += ft_putnbr(n * -1);
	}
	else if (n < 10)
		nb_length += ft_putchar(n + '0');
	else
	{
		nb_length += ft_putnbr(n / 10);
		nb_length += ft_putchar((n % 10) + '0');
	}
	return (nb_length);
}
