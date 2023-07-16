/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 10:24:42 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/17 00:52:35 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	parse_map(char *filename, t_fdf *f)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		terminate(ERR_MAP_INIT);
	f->start = process_map(fd, f);
	close(fd);
	f->map->z_range = f->map->z_max - f->map->z_min;
}

t_point	*process_map(int fd, t_fdf *f)
{
	char	*line;
	t_point	*head;
	t_point	*current;
	int		height;

	head = NULL;
	current = NULL;
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		process_line(line, f, &head, &current);
		line = get_next_line(fd);
		height++;
	}
	f->map->height = height;
	return (head);
}

void	process_line(char *line, t_fdf *f, t_point **head, t_point **cur)
{
	char	**point_arr;
	char	**head_arr;
	int		width;
	t_point	*point;

	point_arr = ft_split(line, ' ');
	width = 0;
	head_arr = point_arr;
	while (*point_arr)
	{
		point = new_point(*point_arr);
		if (!point)
			free_all_point(*head);
		add_point_back(head, cur, point);
		update_altitude(f, point->altitude);
		free(*point_arr);
		point_arr++;
		width++;
	}
	free(head_arr);
	free(line);
	validate_mapsize(width, f, *head);
}
