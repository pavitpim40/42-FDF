/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:53:05 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/03 12:56:38 by ppimchan         ###   ########.fr       */
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
	int					color;
	struct s_coordinate	*next;

}						t_coordinate;

// MAP Detail
typedef struct s_map	
{
	int		width;
	int		height;
	t_coordinate		**coordinate_map;
	int		*colors_arr;
	int		z_min;
	int		z_max;
	int		z_range;
}		t_map;

// fdf detail
typedef struct s_fdf
{
	void		*mlx;
	void		*win;

	void		*img;
	char		*data_addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;

	t_map		*map;
	// t_camera	*camera;
	// t_mouse		*mouse;
}				t_fdf;
// Coordinate Height

// Prototypes

void terminate(char *msg);

t_map *map_init();
t_coordinate *new_coordinate(int x, int y, int z);
void free_split_line(char **split_line);
void read_map(int fd, t_map *map);
void print_map(t_map *map, t_coordinate *head);

int cal_abs(int x, int y);
int cal_max(int x, int y);
int cal_min(int x, int y);
int get_altitude_color(t_map *map,int z );
t_node duplicate_node(int x, int y, int z, int color);
t_node project_isometric(t_node node);
void my_mlx_pixel_put(t_canvas *canvas, int x, int y, int color);
void draw_algorithm_3(int x0, int y0, int xn, int yn, t_canvas *img, int color);
// void ft_putendl_fd(char const *msg, int fd);


#endif