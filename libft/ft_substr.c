/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:18:01 by ncollign          #+#    #+#             */
/*   Updated: 2024/03/11 12:28:09 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_get_alloc_len(size_t s_len, unsigned int start, size_t len)
{
	size_t	alloc_len;

	if ((size_t)start >= s_len)
		return (0);
	if (len < s_len - start)
		alloc_len = len;
	else
		alloc_len = s_len - start;
	return (alloc_len);
}

static void	ft_copy_substr(const char *s, unsigned int start,
		size_t alloc_len, char *substr)
{
	size_t	i;

	i = 0;
	while (i < alloc_len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	alloc_len;
	char	*empty_str;
	char	*substr;

	s_len = ft_strlen(s);
	alloc_len = ft_get_alloc_len(s_len, start, len);
	if (!alloc_len)
	{
		empty_str = malloc(1);
		if (!empty_str)
			return (NULL);
		empty_str[0] = '\0';
		return (empty_str);
	}
	substr = malloc(alloc_len + 1);
	if (!substr)
		return (NULL);
	ft_copy_substr(s, start, alloc_len, substr);
	return (substr);
}
