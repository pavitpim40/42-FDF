/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse-map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:43:55 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/14 14:28:19 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	*process_map(char *filename, t_fdf *f)
{
	int	fd;

	fd = open(filename, O_RDONLY);

	if (fd < 0)
		terminate(ERR_MAP_INIT);
	parse_map(fd, f);
	close(fd);
	return (f->head);
}

void	parse_map(int fd, t_fdf *f)
{
	t_matrix		**matrix;
	char			*axis_string;
	int				axis;

	axis = 0;
	matrix = malloc(sizeof(t_matrix *));
	if (!matrix)
		terminate(ERR_MAP_INIT);
	axis_string = get_next_line(fd);
	while (axis_string)
	{
		extract_line(axis_string, f, axis, matrix);
		axis++;
		axis_string = get_next_line(fd);
	}
	f->map->height = axis;
	f->map->z_range = f->map->z_max - f->map->z_min;
}

void	extract_line(char *axis_string, t_fdf *f, int axis, t_matrix **matrix)
{
	char	**axis_array;
	int		ordinate;
	int		altitude;

	axis_array = ft_split(axis_string, ' ');
	ordinate = 0;
	while (axis_array[ordinate])
	{
		altitude = ft_atoi(axis_array[ordinate]);
		if (axis == 0 && ordinate == 0)
			add_head(f, new_element(axis, ordinate, altitude), matrix);
		else
			add_next(new_element(axis, ordinate, altitude), matrix);
		update_altitude(f, altitude);
		ordinate++;
	}
	if (f->map->width == 0)
		f->map->width = ordinate;
	else if (f->map->width != ordinate)
		terminate(ERR_MAP_INIT);
	free_split_line(axis_array);
	free(axis_string);
}

void	free_split_line(char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i])
	{
		free(split_line[i]);
		i++;
	}
	free(split_line);
}

void	update_altitude(t_fdf *f, int altitude)
{
	if (altitude < f->map->z_min)
		f->map->z_min = altitude;
	if (altitude > f->map->z_max)
		f->map->z_max = altitude;
}
