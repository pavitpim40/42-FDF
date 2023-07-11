/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:53:05 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/11 19:06:36 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

#define FDF_H

#define HEIGHT 1080
#define WIDTH 1920
#define MENU_WIDTH 250
#define ERR_MAP_INIT "Map initialization failed"

#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>
#include "mlx.h"
#include "libft.h"
#include "color.h"
#include "get_next_line.h"

typedef struct s_bresenham
{
	int dx;
	int dy;
	int step;
	int primary_k;
	int primary_n;
	int secondary_k;
	int dp;
	int ds;
	int decision_param;
	int start_pixel;
	int direction;
} t_bresenham;

typedef struct s_canvas
{
	void *img;
	char *addr;
	int bbp;
	int line_length;
	int endian;
} t_canvas;

typedef struct s_node
{
	int x;
	int y;
	int z;
	int color;
	int altitude;
	double percent;
} t_node;

typedef enum
{
	ISOMETRIC,
	PARALLEL
} t_projection;

typedef struct s_coordinate
{
	int x;
	int y;
	int z;
	int axis;
	int ordinate;
	int altitude;
	int color;
	struct s_coordinate *next;

} t_coordinate;

// MAP Detail
typedef struct s_map
{
	int width;
	int height;
	t_coordinate **coordinate_map;
	int cell_size;
	int z_min;
	int z_max;
	int z_range;
} t_map;

typedef struct s_camera
{
	t_projection projection;
	int zoom;
	double alpha;
	double beta;
	double gamma;
	int x_offset;
	int y_offset;
	float z_divisor;

	// for mouse
	int is_press;
	int x;
	int y;
} t_camera;

// fdf detail
typedef struct s_fdf
{
	void *mlx;
	void *win;
	t_canvas *canvas;
	t_map *map;

	t_coordinate *head;
	t_coordinate **coordinate_map;
	t_camera *camera;
	// t_mouse		*mouse;
} t_fdf;
// Coordinate Height

// Prototypes

void terminate(char *msg);


t_coordinate *new_coordinate(int x, int y, int z);




// MAP
t_map 			*init_map();
void			print_map(t_map *map, t_coordinate *head);

t_coordinate 	*process_map(char *filename, t_fdf *f);
void			parse_map(int fd, t_fdf *f);
void			extract_line(char *axis_string, t_fdf *f, int axis, t_coordinate **coordinate_map);
void 			free_split_line(char **split_line);
void			update_altitude(t_fdf *f, int altitude);


// Coordinate-list : Vector
t_coordinate	*new_coordinate(int x, int y, int z);
// void			stack_coordinate(int axis, int ordinate, int altitude, t_coordinate **coordinate_map);
void			add_head(t_fdf *f, t_coordinate *coordinate, t_coordinate **coordinate_map);
void			add_next(t_coordinate *coordinate, t_coordinate **coordinate_map);
int				list_count(t_coordinate *head);




// MATH
int cal_abs(int x, int y);
int cal_max(int x, int y);
int cal_min(int x, int y);
int	cal_avg(int start, int end, double percentage);
void rotate_x(int *y, int *z, double alpha);
void rotate_y(int *x, int *z, double beta);
void rotate_z(int *x, int *y, double gamma);
void iso(int *x, int *y, int z);

// DRAW
void draw_image(t_fdf *fdf);

t_node new_render_node (t_fdf *fdf,int axis,int ordinate,int altitude);
t_coordinate dup_coordinate(int axis,int ordinate,int altitude, int color);
int get_altitude_color(t_map *map, int z);

t_bresenham	*init_bresenham(t_node start, t_node end);
void draw_line(t_node start, t_node end, t_canvas *img);

void pixel_put(t_canvas *canvas, int x, int y, int color);
int get_pixel_color(t_node start, t_node end, t_bresenham *b, int pixel);

t_node coordinate_to_pixel(t_fdf *f, t_coordinate t, int color);
t_node create_project_node(int axis, int ordinate, int altitude, int color, t_map *map);
t_node create_render_node(t_node, int color, int altitude, t_map *map, char *name);



// MLX
t_fdf *init_mlx_and_window();

// Canvas
t_canvas *init_canvas(void *mlx);

// Render 
void render_image(t_fdf *f);

// Mouse
int	mouse_move(int x, int y, t_fdf *f);
int mouse_press(int button, int x, int y, t_fdf *f);
int mouse_release(int button, int x, int y, t_fdf *f);
int mouse_hook(int button, int x, int y, t_fdf *f);

// Keyboard
int	key_hook(int keycode, t_fdf *f);
void free_fdf(t_fdf *f);



#endif