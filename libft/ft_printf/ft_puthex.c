/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <ncollign@student.42luxembou      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:38:00 by ncollign          #+#    #+#             */
/*   Updated: 2024/04/25 18:38:50 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_puthex(unsigned int n, const char format)
{
	int	length;

	length = 0;
	length += ft_itoa_hex(n, format);
	return (length);
}
