/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:53:12 by yim               #+#    #+#             */
/*   Updated: 2023/03/30 11:42:05 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "libft.h"

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

typedef struct s_map
{
	int		width;
	int		height;
	int		floor;
	int		ceiling;
	int		start;
	int		check_player;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	**map;
}	t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	rotation;

}	t_player;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_tex
{
	// void	*n;
	int		n_width;
	int		n_height;
	t_data	n;

	// void	*s;
	int		s_width;
	int		s_height;
	t_data	s;

	// void	*e;
	int		e_width;
	int		e_height;
	t_data	e;

	// void	*w;
	int		w_width;
	int		w_height;
	t_data	w;
}	t_tex;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	struct s_data	data;
	// double			rotate_x;
	// double			rotate_y;
	// double			rotate_z;
	// int				width;
	// int				height;
	// int				scale;
	// int				signal;
	t_player		player;
	t_map			*map;
	int				keys;
	// t_tex			*tex;
	t_tex			tex;

}				t_vars;

// error
int		print_error(char *str, int i);
void	exit_error(char *str, int i, t_map *map);
void	exit_line_error(char *str, int i, char *line, t_map *map);
void	free_all(t_map *map);

//map_parsing
void	map_parsing(char *filename, t_map *map);

// init_texture
void	init_texture(t_map *map, char *line);

// init_color
void	init_color(t_map *map, char *line, char c);

// init_map
void	init_map(t_map *map, char *line, int count);
void	make_map(t_map *map, char *filename, int fd);
void	check_surround_wall(t_map *map);

#endif