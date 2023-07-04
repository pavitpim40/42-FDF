/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 02:02:02 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/05 02:36:20 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"


// t_node create_render_node(t_node t,int color,int altitude, t_map *map, char *name)
// {

// 	t_node new_node;
// 	printf("name: %s\n", name);
// 	printf("<- x:%d y:%d z:%d \n",t.x,t.y,t.z);
// 	new_node.x = t.x;
// 	new_node.y = t.y;
// 	new_node.z = t.z;
// 	new_node.color = color;
// 	new_node.altitude = altitude;
// 	new_node.percent = (double)(altitude - map->z_min) / map->z_range;
// 	iso(&new_node.x, &new_node.y, new_node.z);
// 	printf("-> x:%d y:%d z:%d \n\n",new_node.x,new_node.y,new_node.z);
// 	return new_node;
// }

// t_node create_project_node(int axis,int ordinate,int altitude, int color,t_map *map)
// {
// 	// cal zoom level
// 	t_node new_node;


// 	int zoom_level = 1;
// 	zoom_level  = cal_min(WIDTH / (map->width * 2), HEIGHT / (map->height*2));

// 	int x = ordinate * zoom_level;
// 	int y = axis * zoom_level;


// 	x -= (map->width * zoom_level) / 2;
// 	y -= (map->height * zoom_level) / 2;

// 	new_node.x = x;
// 	new_node.y = y;
// 	new_node.z = altitude * zoom_level /5;
// 	new_node.color = color;
// 		iso(&new_node.x, &new_node.y, new_node.z);
// 	new_node.x+= WIDTH / 2;
// 	new_node.y+=  HEIGHT / 2;
// 	new_node.altitude = altitude;

// 	return (new_node);
// }

t_node coordinate_to_pixel(t_fdf *f,t_coordinate t,int color)
{
	// cal zoom level
	t_node new_node;
	int zoom = f->camera->zoom;

	

	int x = t.ordinate * zoom;
	int y = t.axis * zoom;

	x -= (f->map->width * zoom) / 2;
	y -= (f->map->height * zoom) / 2;
	new_node.x = x;
	new_node.y = y;
	new_node.z = t.altitude * zoom /f->camera->z_divisor;
	new_node.color = color;
	// printf("bef (x,y,z) = (%d,%d,%d) \n",new_node.x,new_node.y,new_node.z);
	
	// // print angle
	// printf("alpha:%f beta:%f gamma:%f\n",f->camera->alpha,f->camera->beta,f->camera->gamma);
	rotate_x(&new_node.y, &new_node.z, f->camera->alpha);
	rotate_y(&new_node.x, &new_node.z, f->camera->beta);
	rotate_z(&new_node.x, &new_node.y, f->camera->gamma);
	// printf("aft (x,y,z) = (%d,%d,%d) \n\n",new_node.x,new_node.y,new_node.z);
	if(f->camera->projection == ISOMETRIC)
		iso(&new_node.x, &new_node.y, new_node.z);
	new_node.x+= f->camera->x_offset+ WIDTH / 2 + f->camera->zoom / 2;
	new_node.y+= f->camera->y_offset+ HEIGHT / 2 + f->camera->zoom / 2;
	new_node.altitude = t.altitude;
	return (new_node);
}



