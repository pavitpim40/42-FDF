/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse-map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 18:43:55 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/14 19:22:33 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	isFDF(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (extension && ft_strncmp(extension, ".fdf", ft_strlen(extension)) == 0)
		return (1);
	return (0);
}

t_matrix	*parse_map(char *filename, t_fdf *f)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free_fdf(f);
		terminate(ERR_MAP_INIT);
	}
	get_matrix(fd, f);
	close(fd);
	return (f->head);
}

// Generate MATRIX from map #M
void	get_matrix(int fd, t_fdf *f)
{
	t_matrix		**matrix;
	char			*axis_string;
	int				axis;

	axis = 0;
	matrix = malloc(sizeof(t_matrix *));
	if (!matrix)
	{
		free_fdf(f);
		terminate(ERR_MAP_INIT);
	}
	axis_string = get_next_line(fd);
	while (axis_string)
	{
		extract_line(axis_string, f, axis, matrix);
		axis++;
		axis_string = get_next_line(fd);
	}
	if(axis_string)
		free(axis_string);
	f->map->height = axis;
	f->map->z_range = f->map->z_max - f->map->z_min;
}

// #M 
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
			add_head(f, new_element(axis, ordinate, altitude, f), matrix);
		else
			add_next(new_element(axis, ordinate, altitude, f), matrix);
		if(f->add_status == -1)
		{
			free_extract_line(axis_string, axis_array);
			free_all(f);
			terminate("map is not valid");
		}
		update_altitude(f, altitude);
		ordinate++;
	}
	printf("f->map->width: %d\n", f->map->width);
	if (f->map->width == 0)
		f->map->width = ordinate;
	else if(ordinate != f->map->width)
	{
		free_extract_line(axis_string, axis_array);
		free_all(f);
		terminate("map is not valid");
	}
	// else if (!is_map_in_range(f->map->width, ordinate))
	// {
	// 	free_extract_line(axis_string, axis_array);
	// 	free_all(f);
	// 	terminate("map is not valid in range");
	// }
	// else if(is_map_in_range(f->map->width, ordinate))
	// {
	// 	if(ordinate > f->map->width)
	// 		f->map->width = ordinate;
	// }
	free_extract_line(axis_string, axis_array);
}

void	free_extract_line(char *axis_string, char **axis_array)
{
	free(axis_string);
	free_split_line(axis_array);
}

int	is_map_in_range(int map_width, int current_width)
{
	if(current_width == map_width)
		return (1);
	else if(current_width == map_width -1)
		return (1);
	else if (current_width == map_width + 1)
		return (1);
	return (0);
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
