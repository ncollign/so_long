/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:01:41 by ncollign          #+#    #+#             */
/*   Updated: 2024/03/11 12:03:14 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s_len;
	int		i;
	char	*memory;

	s_len = ft_strlen(s1) + ft_strlen(s2);
	memory = malloc(s_len + 1);
	if (!memory)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		memory[i] = s1[i];
		i++;
	}
	while (s2[i - ft_strlen(s1)] != '\0')
	{
		memory[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	memory[i] = '\0';
	return (memory);
}
