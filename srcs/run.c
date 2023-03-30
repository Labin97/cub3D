/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:33:01 by minsulee          #+#    #+#             */
/*   Updated: 2023/03/30 17:41:01 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <limits.h>

void	player_init(t_vars *ml_mlx);
void	find_player_pos(t_vars *ml_mlx);
int		on_destroy(t_vars *vars);


void	ml_mlx_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ml_mlx_ceiling(t_vars *vars, int color)
{
	int	half_height;
	int	y;
	int	x;

	y = 0;
	x = 0;
	half_height = SCREEN_HEIGHT / 2;
	while (y < half_height)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			ml_mlx_put_pixel(&vars->data, x, y, color);
			x++;
		}
		y++;
	}
}

void	ml_mlx_floor(t_vars *vars, int color)
{
	int	y;
	int	x;

	y = SCREEN_HEIGHT / 2;
	x = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			ml_mlx_put_pixel(&vars->data, x, y, color);
			x++;
		}
		y++;
	}
}

void	projection_init(t_projection *projection, int x, t_player *player)
{
	projection->camera_x = 2 * (x - 1) / (double)SCREEN_WIDTH - 1;
	projection->raydir_x = player->dir_x + player->plane_x \
	* projection->camera_x;
	projection->raydir_y = player->dir_y + player->plane_y \
	* projection->camera_x;
	projection->hit = 0;
	projection->side = 0;
	if (projection->raydir_x == 0)
		projection->delta_dist_x = __DBL_MAX__;  // 이거 쓸까말까???????????????????????????????????????????????
	else
		projection->delta_dist_x = fabs(1 / projection->raydir_x);
	if (projection->raydir_y == 0)
		projection->delta_dist_y = __DBL_MAX__;  // 여기도있음!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	else
		projection->delta_dist_y = fabs(1 / projection->raydir_y);
	projection->pos_x = player->pos_x;
	projection->pos_y = player->pos_y;
	projection->map_x = (int) player->pos_x;
	projection->map_y = (int) player->pos_y;
}

void	projection_direction_set(t_projection *projection)
{
	if (projection->raydir_x < 0)
	{
		projection->step_x = -1;
		projection->side_dist_x = (projection->pos_x - projection->map_x) * \
		projection->delta_dist_x;
	}
	else
	{
		projection->step_x = 1;
		projection->side_dist_x = (projection->map_x + 1.0 - projection->pos_x) \
		* projection->delta_dist_x;
	}
	if (projection->raydir_y < 0)
	{
		projection->step_y = -1;
		projection->side_dist_y = (projection->pos_y - projection->map_y) * \
		projection->delta_dist_y;
	}
	else
	{
		projection->step_y = 1;
		projection->side_dist_y = (projection->map_y + 1.0 - projection->pos_y) \
		* projection->delta_dist_y;
	}
}

void	projection_shoot(t_map *map, t_projection *projection)
{
	int	hit;

	while (projection->hit == 0)
	{
		if (projection->side_dist_x < projection->side_dist_y)
		{
			projection->side_dist_x += projection->delta_dist_x;
			projection->map_x += projection->step_x;
			projection->side = 0;
		}
		else
		{
			projection->side_dist_y += projection->delta_dist_y;
			projection->map_y += projection->step_y;
			projection->side = 1;
		}
		if (map->map[projection->map_y][projection->map_x] == '1')
			projection->hit = 1;
	}
}

void	projection_point(t_projection *projection)
{
	if (projection->side == 0)
		projection->perp_wall_dist = \
		(projection->side_dist_x - projection->delta_dist_x);
	else
		projection->perp_wall_dist = \
		(projection->side_dist_y - projection->delta_dist_y);
	if (projection->side == 0)
		projection->wall_x = \
		projection->pos_y + projection->perp_wall_dist * projection->raydir_y;
	else
		projection->wall_x = \
		projection->pos_x + projection->perp_wall_dist * projection->raydir_x;
	projection->wall_x -= floor(projection->wall_x);
}

void	projection_height(t_projection *projection)
{
	projection->line_height = (int)(SCREEN_HEIGHT / \
	projection->perp_wall_dist);
	projection->draw_start = -(projection->line_height) / 2 \
	+ SCREEN_HEIGHT / 2;
	if (projection->draw_start < 0)
		projection->draw_start = 0;
	projection->draw_end = (projection->line_height) / 2 + \
	SCREEN_HEIGHT / 2;
	if (projection->draw_end >= SCREEN_HEIGHT)
		projection->draw_end = SCREEN_HEIGHT - 1;
}

void	projection_side(t_projection *projection)
{
	if (projection->side == 1)
	{
		if (projection->step_y < 0)
			projection->side = 0;
		else
			projection->side = 1;
	}
	else
	{
		if (projection->step_x < 0)
			projection->side = 2;
		else
			projection->side = 3;
	}
}

void	projection_texture(t_tex *tex, t_projection *projection)
{
	if (projection->side == 0)
	{
		projection->texture = (int *)tex->n.addr;
		projection->tex_width = tex->n_width;
		projection->tex_height = tex->n_height;
	}
	else if (projection->side == 1)
	{
		projection->texture = (int *)tex->s.addr;
		projection->tex_width = tex->s_width;
		projection->tex_height = tex->s_height;
	}
	else if (projection->side == 2)
	{
		projection->texture = (int *)tex->w.addr;
		projection->tex_width = tex->w_width;
		projection->tex_height = tex->w_height;
	}
	else if (projection->side == 3)
	{
		projection->texture = (int *)tex->e.addr;
		projection->tex_width = tex->e_width;
		projection->tex_height = tex->e_height;
	}
}

void	projection_draw(t_vars *ml_mlx, t_projection *projection, int x)
{
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;

	tex_x = (int)(projection->wall_x * projection->tex_width);
	if (projection->side == 1 || projection->side == 2)
		tex_x = projection->tex_width - tex_x - 1;
	step = 1.0 * projection->tex_height / projection->line_height;
	tex_pos = (projection->draw_start - (SCREEN_HEIGHT / 2) + \
		projection->line_height / 2) * step;
	while (projection->draw_start < projection->draw_end)
	{
		tex_y = (int)(tex_pos) & (int)(projection->tex_height - 1);
		tex_pos += step;
		ml_mlx_put_pixel(&ml_mlx->data, x, projection->draw_start, \
		projection->texture[(int) projection->tex_width * tex_y + tex_x]);
		(projection->draw_start)++;
	}
}

int	project_once(t_vars *ml_mlx, t_map *map, t_player *player)
{
	t_projection	projection;
	int				x;

	ml_mlx_ceiling(ml_mlx, ml_mlx->map->ceiling);
	ml_mlx_floor(ml_mlx, ml_mlx->map->floor);
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		projection_init(&projection, x, player);
		projection_direction_set(&projection);
		projection_shoot(ml_mlx->map, &projection);
		projection_point(&projection);
		projection_height(&projection);
		projection_side(&projection);
		projection_texture(&ml_mlx->tex, &projection);
		projection_draw(ml_mlx, &projection, x);
		x++;
	}
	mlx_put_image_to_window(ml_mlx->mlx, ml_mlx->win, ml_mlx->data.img, 0, 0);
	return (0);
}

static void	ml_mlx_init(t_vars *ml_mlx)
{
	ml_mlx->mlx = mlx_init();
	ml_mlx->win = mlx_new_window(ml_mlx->mlx, \
	SCREEN_WIDTH, SCREEN_HEIGHT, "yiminsu_cub3D");
	ml_mlx->data.img = mlx_new_image(ml_mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	ml_mlx->data.addr = mlx_get_data_addr(ml_mlx->data.img, \
		&(ml_mlx->data.bits_per_pixel), &(ml_mlx->data.line_length), \
		&(ml_mlx->data.endian));
	ml_mlx->keys = 0;
	find_player_pos(ml_mlx);
	player_init(ml_mlx);
}

int	key_press_hook(int key, t_vars *vars)
{
	if (key == 53)
		on_destroy(vars);
	else if (key == 123 && !(vars->keys & 32))
		vars->keys += 32;
	else if (key == 124 && !(vars->keys & 16))
		vars->keys += 16;
	else if (key == 13 && !(vars->keys & 0x8))
		vars->keys += 8;
	else if (key == 0 && !(vars->keys & 0x4))
		vars->keys += 4;
	else if (key == 1 && !(vars->keys & 0x2))
		vars->keys += 2;
	else if (key == 2 && !(vars->keys & 0x1))
		vars->keys += 1;
	return (0);
}

int key_release_hook(int key, t_vars *vars)
{
	if (key == 123 && (vars->keys & 32))
		vars->keys -= 32;
	else if (key == 124 && (vars->keys & 16))
		vars->keys -= 16;
	else if (key == 13 && (vars->keys & 0x8))
		vars->keys -= 8;
	else if (key == 0 && (vars->keys & 0x4))
		vars->keys -= 4;
	else if (key == 1 && (vars->keys & 0x2))
		vars->keys -= 2;
	else if (key == 2 && (vars->keys & 0x1))
		vars->keys -= 1;
	return (0);
}

void	render_next_frame_key_wd(t_vars *vars)
{
	if (vars->keys & 8)
	{
		if (vars->map->map[(int)(vars->player.pos_y)] \
		[(int)(vars->player.pos_x + vars->player.dir_x / 8)] != '1')
			vars->player.pos_x += (vars->player.dir_x / 8);
		if (vars->map->map[(int)(vars->player.pos_y + \
		vars->player.dir_y / 8)][(int)(vars->player.pos_x)] != '1')
			vars->player.pos_y += (vars->player.dir_y / 8);
	}
	else if (vars->keys & 2)
	{
		if (vars->map->map[(int)(vars->player.pos_y)] \
		[(int)(vars->player.pos_x - vars->player.dir_x / 8)] != '1')
			vars->player.pos_x -= (vars->player.dir_x / 8);
		if (vars->map->map[(int)(vars->player.pos_y - \
		vars->player.dir_y / 8)][(int)(vars->player.pos_x)] != '1')
			vars->player.pos_y -= (vars->player.dir_y / 8);
	}
}

void	render_next_frame_key_ad(t_vars *vars)
{
	if (vars->keys & 32)
	{
		vars->player.rotation -= M_PI / 72;
		vars->player.dir_x = +sin(vars->player.rotation);
		vars->player.dir_y = -cos(vars->player.rotation);
		vars->player.plane_x = -vars->player.dir_y;
		vars->player.plane_y = +vars->player.dir_x;
	}
	else if (vars->keys & 16)
	{
		vars->player.rotation += M_PI / 72;
		vars->player.dir_x = +sin(vars->player.rotation);
		vars->player.dir_y = -cos(vars->player.rotation);
		vars->player.plane_x = -vars->player.dir_y;
		vars->player.plane_y = +vars->player.dir_x;
	}
}

void	render_next_frame_key_arrow_lr(t_vars *vars)
{
	if (vars->keys & 1)
	{
		if (vars->map->map[(int)(vars->player.pos_y)] \
		[(int)(vars->player.pos_x + vars->player.plane_x / 8)] != '1')
			vars->player.pos_x += (vars->player.plane_x / 8);
		if (vars->map->map[(int)(vars->player.pos_y + \
		vars->player.plane_y / 8)][(int)(vars->player.pos_x)] != '1')
			vars->player.pos_y += (vars->player.plane_y / 8);
	}
	else if (vars->keys & 4)
	{
		if (vars->map->map[(int)(vars->player.pos_y)] \
		[(int)(vars->player.pos_x - vars->player.plane_x / 8)] != '1')
			vars->player.pos_x -= (vars->player.plane_x / 8);
		if (vars->map->map[(int)(vars->player.pos_y - \
		vars->player.plane_y / 8)][(int)(vars->player.pos_x)] != '1')
			vars->player.pos_y -= (vars->player.plane_y / 8);
	}
}

int	render_next_frame(t_vars *vars)
{
	if (vars->keys)
	{
		if (!((vars->keys & 8) && (vars->keys & 2)))
			render_next_frame_key_wd(vars);
		if (!((vars->keys & 32) && (vars->keys & 16)))
			render_next_frame_key_ad(vars);
		if (!((vars->keys & 4) && (vars->keys & 1)))
			render_next_frame_key_arrow_lr(vars);
		project_once(vars, vars->map, &vars->player);
		if (fabs(vars->player.rotation) >= 6.283185)
			vars->player.rotation = 0;
	}
	return (0);
}

void	find_player_pos(t_vars *ml_mlx)
{
	int		i;
	int		j;

	i = -1;
	while (++i < ml_mlx->map->height)
	{
		j = -1;
		while (++j < ml_mlx->map->width)
		{
			if (ml_mlx->map->map[i][j] == 'N' || ml_mlx->map->map[i][j] == 'S' \
			|| ml_mlx->map->map[i][j] == 'W' || ml_mlx->map->map[i][j] == 'E')
			{
				ml_mlx->player.pos_x = j + 0.501;
				ml_mlx->player.pos_y = i + 0.501;
				if (ml_mlx->map->map[i][j] == 'N')
					ml_mlx->player.rotation = 0;
				else if (ml_mlx->map->map[i][j] == 'S')
					ml_mlx->player.rotation = M_PI;
				else if (ml_mlx->map->map[i][j] == 'W')
					ml_mlx->player.rotation = M_PI * 1.5;
				else if (ml_mlx->map->map[i][j] == 'E')
					ml_mlx->player.rotation = M_PI / 2;
			}
		}
	}
}

void	player_init(t_vars *ml_mlx)
{
	ml_mlx->player.dir_x = +sin(ml_mlx->player.rotation);
	ml_mlx->player.dir_y = -cos(ml_mlx->player.rotation);
	ml_mlx->player.plane_x = -ml_mlx->player.dir_y;
	ml_mlx->player.plane_y = +ml_mlx->player.dir_x;
}

void leak_check(void)
{
	system("leaks cub3D");
}

void	tex_img(t_vars *ml_mlx)
{
	ml_mlx->tex.n.img = 0;
	ml_mlx->tex.n.img = mlx_xpm_file_to_image(ml_mlx->mlx, \
	ml_mlx->map->no_path, &ml_mlx->tex.n_width, &ml_mlx->tex.n_height);
	ml_mlx->tex.n.addr = 0;
	ml_mlx->tex.n.addr = mlx_get_data_addr(ml_mlx->tex.n.img, \
	&ml_mlx->tex.n.bits_per_pixel, &ml_mlx->tex.n.line_length, \
	&ml_mlx->tex.n.endian);
	ml_mlx->tex.s.img = mlx_xpm_file_to_image(ml_mlx->mlx, \
	ml_mlx->map->so_path, &ml_mlx->tex.s_width, &ml_mlx->tex.s_height);
	ml_mlx->tex.s.addr = mlx_get_data_addr(ml_mlx->tex.s.img, \
	&ml_mlx->tex.s.bits_per_pixel, &ml_mlx->tex.s.line_length, \
	&ml_mlx->tex.s.endian);
	ml_mlx->tex.e.img = mlx_xpm_file_to_image(ml_mlx->mlx, \
	ml_mlx->map->ea_path, &ml_mlx->tex.e_width, &ml_mlx->tex.e_height);
	ml_mlx->tex.e.addr = mlx_get_data_addr(ml_mlx->tex.e.img, \
	&ml_mlx->tex.e.bits_per_pixel, &ml_mlx->tex.e.line_length, \
	&ml_mlx->tex.e.endian);
	ml_mlx->tex.w.img = mlx_xpm_file_to_image(ml_mlx->mlx, \
	ml_mlx->map->we_path, &ml_mlx->tex.w_width, &ml_mlx->tex.w_height);
	ml_mlx->tex.w.addr = mlx_get_data_addr(ml_mlx->tex.w.img, \
	&ml_mlx->tex.w.bits_per_pixel, &ml_mlx->tex.w.line_length, \
	&ml_mlx->tex.w.endian);
}

int	on_destroy(t_vars *vars)
{
	printf("destroying...\n");
	free_all(vars->map);
	mlx_destroy_image(vars->mlx, vars->tex.n.img);
	mlx_destroy_image(vars->mlx, vars->tex.e.img);
	mlx_destroy_image(vars->mlx, vars->tex.s.img);
	mlx_destroy_image(vars->mlx, vars->tex.w.img);
	mlx_destroy_image(vars->mlx, vars->data.img);
	mlx_destroy_window(vars->mlx, vars->win);


	exit(0);
}

int main(int argc, char **argv)
{
	t_map	map;
	t_vars	ml_mlx;

	atexit(leak_check);
	if (argc != 2)
		return (print_error("argument error", 1));
	map_parsing(argv[1], &map);
	ml_mlx.map = &map;
	ml_mlx_init(&ml_mlx);
	tex_img(&ml_mlx);
	project_once(&ml_mlx, &map, &ml_mlx.player);
	mlx_hook(ml_mlx.win, 2, 1L << 0, key_press_hook, &ml_mlx);
	mlx_hook(ml_mlx.win, 3, 1L << 1, key_release_hook, &ml_mlx);
	mlx_hook(ml_mlx.win, 17, 0, on_destroy, &ml_mlx);
	mlx_loop_hook(ml_mlx.mlx, render_next_frame, &ml_mlx);
	mlx_loop(ml_mlx.mlx);
	// free_all(&map);
}
