/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 02:20:53 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/02 15:22:44 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static	char	*extract_full_line(char *storage)
{
	char		*full_line;
	int			index;
	int			len;

	if (!storage)
		return (NULL);
	len = 0;
	while (storage[len] && storage[len] != '\n')
		len++;
	full_line = malloc(sizeof(char) * len + 2);
	if (!full_line)
		return (NULL);
	index = 0;
	while (index < len)
	{
		full_line[index] = storage[index];
		index++;
	}
	if (storage[index] == '\n')
		full_line[index++] = '\n';
	full_line[index] = '\0';
	return (full_line);
}

static	char	*truncate_storage(char *storage)
{
	int		len;
	int		i;
	int		index;
	char	*new_storage;

	len = ft_strlen(storage);
	index = ft_char_index(storage, '\n');
	if (index == -1 || len == index + 1)
	{
		free(storage);
		return (NULL);
	}
	i = 0;
	new_storage = malloc(sizeof(char) * (len - index));
	if (!new_storage)
		return (NULL);
	while (storage && i < (len - index - 1))
	{
		new_storage[i] = storage[i + index + 1];
		i++;
	}
	new_storage[i] = '\0';
	free(storage);
	return (new_storage);
}

static	char	*storage_join(char *storage, char *buffer)
{
	char		*new_storage;
	size_t		i;
	size_t		j;

	new_storage = malloc(ft_strlen(storage) + ft_strlen(buffer) + 1);
	if (!new_storage)
		return (NULL);
	i = 0;
	while (storage && storage[i])
	{
		new_storage[i] = storage[i];
		i++;
	}
	j = 0;
	while (buffer[j])
	{
		new_storage[i + j] = buffer[j];
		j++;
	}
	new_storage[i + j] = '\0';
	if (storage)
		free(storage);
	return (new_storage);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	int				read_byte;
	char static		*storage;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_byte = 1;
	while (read_byte > 0 && ft_char_index(storage, '\n') == -1)
	{
		read_byte = (int)read(fd, buffer, BUFFER_SIZE);
		if (read_byte != 0 && read_byte != -1)
		{
			buffer[read_byte] = '\0';
			storage = storage_join(storage, buffer);
		}
	}
	free(buffer);
	buffer = extract_full_line(storage);
	storage = truncate_storage(storage);
	return (buffer);
}
