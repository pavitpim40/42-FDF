/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:53:05 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/04 13:10:38 by ppimchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

# define HEIGHT			1080
# define WIDTH			1920
# define MENU_WIDTH		250
# define ERR_MAP_INIT	"Map initialization failed"

#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>

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
	int decision_parameter;
	int start_pixel;
} t_bresenham;

typedef struct s_canvas
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} 	t_canvas;

typedef struct s_node
{
	int x;
	int y;
	int z;
	int color;
	int altitude;
	double percent;
} 	t_node;

typedef enum
{
	ISOMETRIC,
	PARALLEL
}	t_projection;

typedef struct 			s_coordinate
{
	int					x;
	int					y;
	int					z;
	// int  			    axis;
	// int					ordinate;
	// int					altitude;
	int					color;
	struct s_coordinate	*next;

}						t_coordinate;

// MAP Detail
typedef struct s_map	
{
	int		width;
	int		height;
	t_coordinate		**coordinate_map;
	int		cell_size;
	int		z_min;
	int		z_max;
	int		z_range;
}		t_map;

// fdf detail
typedef struct s_fdf
{
	void			*mlx;
	void			*win;
	t_canvas		*canvas;
	t_map			*map;
	
	t_coordinate 	*head;
	t_coordinate 	**coordinate_map;
	
	// t_camera	*camera;
	// t_mouse		*mouse;
}				t_fdf;
// Coordinate Height

// Prototypes

void terminate(char *msg);

t_map *init_map();
t_coordinate *new_coordinate(int x, int y, int z);
void free_split_line(char **split_line);

t_coordinate *process_map (char *filename,t_fdf *f);
void print_map(t_map *map, t_coordinate *head);

int cal_abs(int x, int y);
int cal_max(int x, int y);
int cal_min(int x, int y);

// geometry
void rotate_x(int *y, int *z, double alpha);
void rotate_y(int *x, int *z, double beta);
void rotate_z(int *x, int *y, double gamma);
void iso(int *x, int *y, int z);

void draw_image (t_fdf *fdf);
int get_altitude_color(t_map *map,int z );
// int get_pixel_color(t_node start, t_node end, int pixel_range, int pixel, int start_pixel);
int get_pixel_color(t_node start, t_node end, t_bresenham *b, int pixel);


// t_node create_render_node(int x, int y,int z,int color,int altitude, t_map *map);
t_node create_project_node(int axis,int ordinate,int altitude, int color,t_map *map);
t_node create_render_node(t_node,int color,int altitude, t_map *map, char *name);

void pixel_put(t_canvas *canvas, int x, int y, int color);
void draw_line(t_node start,t_node end, t_canvas *img);
// void ft_putendl_fd(char const *msg, int fd);


#endif