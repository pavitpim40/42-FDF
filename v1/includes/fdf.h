/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppimchan <ppimchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:53:05 by ppimchan          #+#    #+#             */
/*   Updated: 2023/07/02 23:28:29 by ppimchan         ###   ########.fr       */
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
// void ft_putendl_fd(char const *msg, int fd);


#endif