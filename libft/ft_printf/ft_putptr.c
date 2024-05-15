/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembou      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:40:51 by ncollign          #+#    #+#             */
/*   Updated: 2024/04/25 18:41:30 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putptr(unsigned long int ptr)
{
	int	length;

	length = 0;
	if (ptr == 0)
		length += ft_putstr("(nil)");
	else
	{
		length += ft_putstr("0x");
		length += ft_itoa_hex(ptr, 'P');
	}
	return (length);
}
