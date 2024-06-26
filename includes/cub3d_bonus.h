/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:53:12 by yim               #+#    #+#             */
/*   Updated: 2023/03/31 14:31:56 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>
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
	int		n_width;
	int		n_height;
	t_data	n;

	int		s_width;
	int		s_height;
	t_data	s;

	int		e_width;
	int		e_height;
	t_data	e;

	int		w_width;
	int		w_height;
	t_data	w;
}	t_tex;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	struct s_data	data;
	t_player		player;
	t_map			*map;
	int				keys;
	t_tex			tex;

}				t_vars;

typedef struct s_projection
{
	double	pos_x;
	double	pos_y;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	tex_width;
	double	tex_height;
	double	wall_x;
	double	perp_wall_dist;
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		*texture;
}	t_projection;

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
void	make_map(t_map *map, int fd);
void	check_surround_wall(t_map *map);

// projection
void	projection_draw(t_vars *ml_mlx, t_projection *projection, int x);
void	projection_texture(t_tex *tex, t_projection *projection);
void	projection_side(t_projection *projection);
void	projection_height(t_projection *projection);

//hook
int		key_press_hook(int key, t_vars *vars);
int		key_release_hook(int key, t_vars *vars);

//mlx
void	ml_mlx_ceiling(t_vars *vars, int color);
void	ml_mlx_floor(t_vars *vars, int color);
void	ml_mlx_put_pixel(t_data *data, int x, int y, int color);

//main
void	ml_mlx_init(t_vars *ml_mlx);
void	texture_set(t_vars *ml_mlx);
int		project_once(t_vars *ml_mlx, t_player *player);
int		render_next_frame(t_vars *vars);
int		destroy(t_vars *vars);

#endif