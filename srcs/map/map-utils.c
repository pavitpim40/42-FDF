/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 22:07:59 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/18 23:52:58 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_altitude(t_fdf *f, int altitude)
{
	if (altitude < f->map->z_min)
		f->map->z_min = altitude;
	if (altitude > f->map->z_max)
		f->map->z_max = altitude;
}

int	is_fdf(char *filename)
{
	char	*extension;

	extension = ft_strrchr(filename, '.');
	if (extension && ft_strncmp(extension, ".fdf", ft_strlen(extension)) == 0)
		return (1);
	return (0);
}

int	is_exist(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	close(fd);
	if (fd < 0)
		return (0);
	else
		return (1);
}

void	validate_mapsize(int width, t_fdf *f, t_point *head)
{
	if (!f->map->width)
		f->map->width = width;
	else if (width != f->map->width)
	{
		free_all_point(head);
		terminate("Invalid map");
	}
}
