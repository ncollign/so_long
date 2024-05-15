/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembou      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:42:34 by ncollign          #+#    #+#             */
/*   Updated: 2024/04/25 18:43:31 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putunbr(unsigned int n)
{
	int	nb_length;

	nb_length = 0;
	if (n < 10)
		nb_length += ft_putchar(n + '0');
	else
	{
		nb_length += ft_putnbr(n / 10);
		nb_length += ft_putchar((n % 10) + '0');
	}
	return (nb_length);
}
