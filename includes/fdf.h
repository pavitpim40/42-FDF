/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:53:05 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/16 15:21:40 by ppimchan         ###   ########.fr       */
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


typedef enum
{
	ISOMETRIC,
	PARALLEL
} t_projection;

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
	int altitude;
	int color;
} t_node;


typedef struct s_map
{
	int width;
	int height;
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
	int is_press;
	int x;
	int y;
} t_camera;

// point
typedef struct s_point
{
	int altitude;
	int default_color;
	struct s_point *next;
} t_point;

typedef struct s_fdf
{
	void *mlx;
	void *win;
	t_canvas 	*canvas;
	t_map 		*map;
	t_camera 	*camera;
	
	// point 
	t_point 	*start;
	int			*h_mtx;
	int			*c_mtx;
	int		have_default_color;
} t_fdf;



// MLX,Canvas
t_fdf *init_mlx_and_window();
t_canvas *init_canvas(void *mlx);

// Render
void			render_image(t_fdf *f);
void			rerender(t_fdf *fdf);

// MAP Init
t_map 			*init_map();
int				isFDF(char *filename);
void 			terminate(char *msg);

// Parse Map
void			parse_map_new(char *filename, t_fdf *f);
int				ft_isnum_base(char *str, int base);
int				ft_whitespace(char c);
t_point 		*new_point(char *point_str);
void 			free_all_point(t_point *point);
void 			print_all_point(t_point *head);

// Matrix
void 			create_matrix(t_fdf *f);

// Draw
void			draw_image_new(t_fdf *fdf);

void			draw_each_row_new(t_fdf *fdf, int axis);
t_node			create_node(t_fdf *f, int axis, int ordinate, int altitude);
int 			get_altitude_color(t_map *map, int z);

void 			draw_line(t_node start, t_node end, t_canvas *img);
t_bresenham		*init_bresenham(t_node start, t_node end);

void 			draw_pixel(t_canvas *canvas, int x, int y, int color);
int 			get_pixel_color(t_node start, t_node end, t_bresenham *b, int pixel);

// Free
void			free_fdf(t_fdf *f);
void			free_all(t_fdf *f);
void 			free_matrix(t_fdf *fdf);
void 			free_fdf(t_fdf *f);

// MATH
int cal_abs(int x, int y);
int cal_max(int x, int y);
int cal_min(int x, int y);
int	cal_avg(int start, int end, double percentage);

// Geometry
void rotate_x(int *y, int *z, double alpha);
void rotate_y(int *x, int *z, double beta);
void rotate_z(int *x, int *y, double gamma);
void iso(int *x, int *y, int z);


// ### EVENT

// # Keyboard
int	key_hook(int keycode, t_fdf *f);

// # Mouse
int	mouse_move(int x, int y, t_fdf *f);
int mouse_press(int button, int x, int y, t_fdf *f);
int mouse_release(int button, int x, int y, t_fdf *f);

// # Projection
void	isometric_projection (t_fdf *f);
void	topview_projection (t_fdf *f);
// # Shift
void	shift_left(t_fdf *f);
void	shift_rigth(t_fdf *f);
void	shift_up(t_fdf *f);
void	shift_down(t_fdf *f);
// # Zoom
void	zoom_in(t_fdf *f);
void	zoom_out(t_fdf *f);
// # Angle
void	alpha_increase(t_fdf *f);
void	alpha_decrease(t_fdf *f);
void	beta_increase(t_fdf *f);
void	beta_decrease(t_fdf *f);
void	gamma_increase(t_fdf *f);
void	gamma_decrease(t_fdf *f);
void	reset(t_fdf *f);




#endif