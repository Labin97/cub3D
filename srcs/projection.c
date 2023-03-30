/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project_once.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:15:18 by yim               #+#    #+#             */
/*   Updated: 2023/03/30 19:17:54 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		projection->delta_dist_x = __DBL_MAX__;
		projection->delta_dist_x = fabs(1 / projection->raydir_x);
	if (projection->raydir_y == 0)
		projection->delta_dist_y = __DBL_MAX__;
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
