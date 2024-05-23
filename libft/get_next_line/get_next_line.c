/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncollign <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 17:22:24 by ncollign          #+#    #+#             */
/*   Updated: 2024/05/15 14:59:00 by ncollign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"	

static char	*read_line(int fd, char *buf, char *backup)
{
	int		nb_byte;
	char	*char_temp;

	nb_byte = 1;
	while (nb_byte != 0)
	{
		nb_byte = read(fd, buf, BUFFER_SIZE);
		if (nb_byte == -1)
			return (NULL);
		else if (nb_byte != 0)
		{
			buf[nb_byte] = '\0';
			if (!backup)
				backup = ft_strdup("");
			char_temp = backup;
			backup = ft_strjoin(backup, buf);
			ft_free(&char_temp);
			if (ft_strchr (buf, '\n'))
				nb_byte = 0;
		}
	}
	return (backup);
}

static char	*extract_line(char *line)
{
	size_t	count;
	char	*backup;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0' || line[1] == '\0')
		return (NULL);
	backup = ft_substr(line, count + 1, (int)ft_strlen(line) - count);
	if (*backup == '\0')
		ft_free(&backup);
	line[count + 1] = '\0';
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*backup[4096];

	if (BUFFER_SIZE <= 0 || fd > 4095 || fd < 0)
		return (NULL);
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (0);
	line = read_line(fd, buf, backup[fd]);
	ft_free(&buf);
	if (!line)
		return (NULL);
	backup[fd] = extract_line(line);
	return (line);
}
