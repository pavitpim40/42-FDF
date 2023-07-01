/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:48:49 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/02 03:29:03 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include "libft.h"
#include <limits.h>
#include <errno.h>
#include <stdio.h>

typedef struct s_canvas
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_canvas;

typedef struct s_node
{
	int x;
	int y;
	int z;
	int color;
} t_node;

void my_mlx_pixel_put(t_canvas *canvas, int x, int y, int color)
{
	char *pos;

	pos = canvas->addr + (y * canvas->line_length + x * (canvas->bits_per_pixel / 8));
	*(unsigned int *)pos = color;

	// hex for ornage : 0x00FFA500
}

int cal_abs(int x, int y)
{
	if (y > x)
		return y - x;
	else
		return x - y;
}

int cal_max(int x, int y)
{
	if (x > y)
		return x;
	else
		return y;
}

int cal_min(int x, int y)
{
	if (x < y)
		return x;
	else
		return y;
}

// for dx > dy
void draw_algorithm(int x0, int y0, int xn, int yn, t_canvas *img, int color)
{

	int xk = x0;
	int yk = y0;
	int dx = cal_abs(x0, xn);
	int dy = cal_abs(y0, yn);
	int step;
	if (yn > y0)
	{
		step = 1;
	}
	else
	{
		step = -1;
	}
	int decision_parameter = 2 * dy - dx;

	while (xk <= xn)
	{
		my_mlx_pixel_put(img, xk, yk, color);
		xk += 1;
		if (decision_parameter < 0)
		{
			decision_parameter = decision_parameter + (2 * dy);
		}
		else
		{
			decision_parameter = decision_parameter + (2 * dy) - (2 * dx);
			yk += step;
		}
	}
}

// for dy > dx
void draw_algorithm_2(int x0, int y0, int xn, int yn, t_canvas *img, int color)
{

	int xk = x0;
	int yk = y0;
	int dx;					  // cal dx -> not cal dx
	int dy = cal_abs(y0, yn); // not cal dx -> calc dy
	int step;
	if (xn > x0)
	{				  // yn > xn
		dx = xn - x0; // swap dy-dx
		step = 1;
	}
	else
	{
		dx = x0 - xn; // swap dy->dx
		step = -1;
	}
	int decision_parameter = 2 * dx - dy;

	while (yk <= yn)
	{
		// xk <= xn
		my_mlx_pixel_put(img, xk, yk, color); // same
		yk += 1;
		if (decision_parameter < 0)
		{
			decision_parameter = decision_parameter + (2 * dx); // swap dy -> dx
		}
		else
		{
			decision_parameter = decision_parameter + (2 * dx) - (2 * dy); // swap dy->dx and dx->dy
			xk += step;
		}
	}
}

// Generalize Draw line Algorithm
void draw_algorithm_3(int x0, int y0, int xn, int yn, t_canvas *img, int color)
{
	int dx = cal_abs(x0, xn);
	int dy = cal_abs(y0, yn);
	int step = 1;

	// #2 Calc step
	int primary_k;
	int primary_n;
	int secondary_k;
	int dp = cal_max(dx, dy);
	int ds = cal_min(dx, dy);

	// printf("dx : %d\n", dx);
	// printf("dy : %d\n", dy);

	if (dx >= dy)
	{
		primary_k = cal_min(x0, xn);
		primary_n = cal_max(x0, xn);
		secondary_k = primary_k == x0 ? y0 : yn;
		if (secondary_k > cal_min(y0, yn))
			step = -1;
		printf("X dominate\n");
	}
	else
	{
		primary_k = cal_min(y0, yn);
		primary_n = cal_max(y0, yn);
		secondary_k = primary_k == y0 ? x0 : xn;
		if (secondary_k > cal_min(x0, xn))
			step = -1;
		printf("Y dominate\n");
	}
	printf("primary_k : %d\n", primary_k);
	printf("primary_n : %d\n", primary_n);
	printf("secondary_k : %d\n", secondary_k);

	int decision_parameter = 2 * ds - dp;
	
	while (primary_k <= primary_n)
	{ // change** yk <= yn
		
		if (dx >= dy)
		{
			// printf("Pair : (%d,%d)\n", primary_k, secondary_k);
			my_mlx_pixel_put(img, primary_k, secondary_k, color);
		}

		else{
			my_mlx_pixel_put(img, secondary_k, primary_k, color);
			// printf("Pair : (%d,%d)\n", primary_k, secondary_k);
		}
			
		primary_k += 1; // ***change
		if (decision_parameter < 0)
		{
			decision_parameter = decision_parameter + (2 * ds);
		}
		else
		{
			decision_parameter = decision_parameter + (2 * ds) - (2 * dp);
			secondary_k += step; // ***change
		}
	}
	printf("endline-------------------\n");
}

void draw_algorithm_4(int *start, int *end, t_canvas *canvas, int color)
{
	int dx = cal_abs(start[0], end[0]);
	int dy = cal_abs(start[1], end[1]);
	int step = 1;

	// #2 Calc step
	int primary_k;
	int primary_n;
	int secondary_k;
	int dp = cal_max(dx, dy);
	int ds = cal_min(dx, dy);

	if (dx >= dy)
	{
		primary_k = start[0];	// x0
		secondary_k = start[1]; // yn
		primary_n = end[0];		// xn
		if (end[1] < start[1])
			step = -1;
	}
	else
	{
		primary_k = start[1];	// y0
		primary_n = end[1];		// yn
		secondary_k = start[0]; // x0
		if (end[0] < start[0])
			step = -1;
	}

	int decision_parameter = 2 * ds - dp;
	while (primary_k <= primary_n)
	{ // change** yk <= yn
		if (dx >= dy)
			my_mlx_pixel_put(canvas, primary_k, secondary_k, color);
		else
			my_mlx_pixel_put(canvas, secondary_k, primary_k, color);
		primary_k += 1; // ***change
		if (decision_parameter < 0)
		{
			decision_parameter = decision_parameter + (2 * ds);
		}
		else
		{
			decision_parameter = decision_parameter + (2 * ds) - (2 * dp);
			secondary_k += step; // ***change
		}
	}
}

// int	read_map()

t_map *map_init()
{
	t_map *map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		terminate(ERR_MAP_INIT);
	ft_bzero(map, sizeof(t_map));
	map->width = 0;
	map->height = 0;
	map->coords_arr = NULL;
	map->colors_arr = NULL;
	map->z_min = INT_MAX; // why ?
	map->z_max = INT_MIN; // why ?
	map->z_range = 0;
	return (map);
}

static void rotate_x(int *y, int *z, double alpha)
{
	int previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

static void rotate_y(int *x, int *z, double beta)
{
	int previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

static void rotate_z(int *x, int *y, double gamma)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}

// function for duplicate t_node
t_node duplicate_node(int x, int y, int z, int color)
{

	t_node new_node;
	new_node.x = x;
	new_node.y = y;
	new_node.z = z;
	new_node.color = color;
	return new_node;
}
// function for iso
void iso(int *x, int *y, int z)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);

}

// function for project isometric from node
t_node project_isometric(t_node node)
{
	// isometric angle in alpha beta grammar
	double alpha = 0;
	double beta = 0;
	double gamma = 0;
	rotate_x(&node.y, &node.z, alpha);
	rotate_y(&node.x, &node.z, beta);
	rotate_z(&node.x, &node.y, gamma);
	printf("node.x , node.y , node.z : (%d, %d, %d)\n", node.x, node.y, node.z);
	iso(&node.x, &node.y, node.z);
	// add offset for x and y
	node.x += 600;
	node.y += 0;
	return node;
}

int main(void)
{
	void *mlx;
	void *mlx_win;
	t_canvas canvas;

	// MAP
	// t_map	*map;
	// map = map_init();

	// ReadMAP
	// int fd;
	// fd = open("maps/42.fdf", O_RDONLY);

	// t_coordinate *coordinate_stack;
	// coordinate_stack = NULL;

	// FOR START MLX
	mlx = mlx_init();

	// FOR START WINDOW
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");

	// FOR START IMAGE
	canvas.img = mlx_new_image(mlx, 1920, 1080);
	canvas.addr = mlx_get_data_addr(canvas.img, &canvas.bits_per_pixel, &canvas.line_length,
									&canvas.endian);
	printf("bits_per_pixel : %d\n", canvas.bits_per_pixel);
	printf("line_length : %d\n", canvas.line_length);
	printf("endian : %d\n", canvas.endian);

	int x0 = 200;
	int xn = 800;
	int y0 = 200;
	int yn = 800;
	int z0 = 0;
	int zn = 0;
	// create t_node for rectangle
	t_node node_1 = {x0, y0, z0, 0x00FF0000};
	t_node node_2 = {xn, y0, zn, 0x00FF0000};
	t_node node_3 = {xn, yn, zn, 0x00FF0000};
	t_node node_4 = {x0, yn, z0, 0x00FF0000};

	// for Top line - RED
	t_node p1 = project_isometric(duplicate_node(node_1.x, node_1.y, node_1.z, 0x00FF0000));
	t_node p2 = project_isometric(duplicate_node(node_2.x, node_2.y, node_2.z, 0x00FF0000));
	printf("p1 : (%d,%d)\n", p1.x, p1.y);
	printf("p2 : (%d,%d)\n", p2.x, p2.y);
	draw_algorithm_3(p1.x, p1.y, p2.x, p2.y, &canvas, 0x00FF0000);
	draw_algorithm_3(node_1.x, node_1.y, node_2.x, node_2.y, &canvas, 0x00FF0000);

	// for Right Line - ORANGE
	t_node p3 = project_isometric(duplicate_node(node_2.x, node_2.y, node_2.z, 0x00FF0000));
	t_node p4 = project_isometric(duplicate_node(node_3.x, node_3.y, node_3.z, 0x00FF0000));
	printf("p3 : (%d,%d)\n", p3.x, p3.y);
	printf("p4 : (%d,%d)\n", p4.x, p4.y);
	draw_algorithm_3(p3.x, p3.y, p4.x, p4.y, &canvas, 0x00FFA500);
	draw_algorithm_3(node_2.x, node_2.y, node_3.x, node_3.y, &canvas, 0x00FFA500);

	// for Bottom Line - GREEN
	t_node p5 = project_isometric(duplicate_node(node_3.x, node_3.y, node_3.z, 0x0000FF00));
	t_node p6 = project_isometric(duplicate_node(node_4.x, node_4.y, node_4.z, 0x0000FF00));
	printf("p5 : (%d,%d)\n", p5.x, p5.y);
	printf("p6 : (%d,%d)\n", p6.x, p6.y);
	draw_algorithm_3(p5.x, p5.y, p6.x, p6.y, &canvas, 0x0000FF00);
	draw_algorithm_3(node_3.x, node_3.y, node_4.x, node_4.y, &canvas, 0x0000FF00);

	// for Left Line - BLUE
	t_node p7 = project_isometric(duplicate_node(node_4.x, node_4.y, node_4.z, 0x000000FF));
	t_node p8 = project_isometric(duplicate_node(node_1.x, node_1.y, node_1.z, 0x000000FF));
	printf("p7 : (%d,%d)\n", p7.x, p7.y);
	printf("p8 : (%d,%d)\n", p8.x, p8.y);
	draw_algorithm_3(p7.x, p7.y, p8.x, p8.y, &canvas, 0x000000FF);
	draw_algorithm_3(node_4.x, node_4.y, node_1.x, node_1.y, &canvas, 0x000000FF);


	// hex for ornage : 0x00FFA500
	// for Top Line
	// t_node p5 = project_isometric(duplicate_node(node_3.x, node_3.y, node_3.z, 0x00FF0000));
	// t_node p6 = project_isometric(duplicate_node(node_4.x, node_4.y, node_4.z, 0x00FF0000));
	// printf("p5.x : %d\n", p5.x);
	// printf("p5.y : %d\n", p5.y);
	// printf("p6.x : %d\n", p6.x);
	// printf("p6.y : %d\n", p6.y);
	// draw_algorithm_3(p5.x, p5.y, p6.x, p6.y, &canvas, 0x00FF0000);
	// draw_algorithm_3(node_3.x,node_3.y,node_4.x,node_4.y,&canvas,0x00FF0000);
	// draw left line
	// draw_algorithm_3(node_4.x,node_4.y,node_1.x,node_1.y,&canvas,0x00FF0000);

	// draw_algorithm_4(node_1,node_2,&canvas,0x00FF0000);

	// Bottom line
	// draw_algorithm_3(x0,yn,xn,yn,&canvas,0x00FF0000);

	// draw_algorithm_3(200,200,200,800,&canvas,0x00FF0000);
	// draw_algorithm_3(800,200,800,800,&canvas,0x00FFA500);

	mlx_put_image_to_window(mlx, mlx_win, canvas.img, 0, 0);
	mlx_loop(mlx);
}

// 	while (y_start < y_end)