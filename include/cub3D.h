/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 09:34:56 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/11 14:34:44 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>

# define VERTICAL 1
# define HORIZONTAL 0
# define WIN_WIDTH 800
# define WIN_HIEGHT 800
# define GRID_WIDTH 60
# define GRID_HIEGHT 60
# define FOV (2 * M_PI / 2)
#include <stdio.h>
typedef enum s_num
{
	NORTH = 0,
	SOUTH,
	WEST,
	EAST,
	CEIL,
	FLOOR,
	MAP,
	NEW_LINE
}	t_num;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		byts_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_player
{
	double	x_pos;
	double	y_pos;
	double	angle;
	int		y_step;
	int		x_step;
}			t_player;

typedef struct s_dda
{
	double	x_pos;
	double	y_pos;
	double	h_to_h;
	double	v_to_v;
	double	h_dist;
	double	v_dist;
	int		x_step;
	int		y_step;
	double	angle;
	int		hit_wall;
}			t_dda;

typedef struct s_info
{
	void		*mlx;
	void		*win;
	t_img		*img;
	char		**map;
	t_player	player;
	void		*wall_imgs[4];
	int			wall_width[4];
	int			wall_height[4];
	int			color_floor;
	int			color_ceil;
}				t_info;


int		parser(t_info *info, char *file);
int		print_error(char *msg1);
int		print_error2(char *msg1, char *msg2);
int		print_error3(char *msg1, char *file, char *end);
int		check_map(char **map);
int		parse_map(t_info *info, char *file, size_t *offset);
char	*read_file(char *map_path);
void	free_map(char **map);
void	destroy_info(t_info *info);
int		parse_element(t_info *info, char *file, size_t *offset, int type);
int		parse_element(t_info *info, char *file, size_t *offset, int type);


int		start_game(t_info *info);
void 	draw_img(t_info *info);
int		len_map(char **map);
#endif