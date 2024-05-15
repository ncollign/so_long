/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:20:06 by ncollign          #+#    #+#             */
/*   Updated: 2024/03/11 11:27:31 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*memory;

	if (SIZE_MAX / num < size)
		return (NULL);
	memory = malloc(num * size);
	if (memory == NULL)
		return (NULL);
	ft_bzero(memory, num * size);
	return (memory);
}
