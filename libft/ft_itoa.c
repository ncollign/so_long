/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:34:02 by ncollign          #+#    #+#             */
/*   Updated: 2024/03/11 11:38:00 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static size_t	ft_sign(int n)
{
	int	sign;

	if (n < 0)
		sign = -1;
	else
		sign = 1;
	return (sign);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	size_t	i;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = ft_sign(n);
	len = ft_intlen(n);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	str[len] = '\0';
	if (n == 0)
		str[i] = '0';
	while (n != 0)
	{
		str[--len] = '0' + (n % 10) * sign;
		n /= 10;
	}
	if (sign == -1)
		str[i] = '-';
	return (str);
}
