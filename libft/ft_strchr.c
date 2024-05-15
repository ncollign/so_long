/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:32:15 by ncollign          #+#    #+#             */
/*   Updated: 2024/03/11 12:32:55 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *src, int c)
{
	while (*src != '\0')
	{
		if (*src == (unsigned char)c)
			return ((char *)src);
		src++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)src);
	return (NULL);
}
