/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:10:13 by yim               #+#    #+#             */
/*   Updated: 2023/03/31 14:32:32 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ml_mlx_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	player_init(t_vars *ml_mlx)
{
	ml_mlx->player.dir_x = +sin(ml_mlx->player.rotation);
	ml_mlx->player.dir_y = -cos(ml_mlx->player.rotation);
	ml_mlx->player.plane_x = -ml_mlx->player.dir_y;
	ml_mlx->player.plane_y = +ml_mlx->player.dir_x;
}

void	find_player_pos(t_vars *ml_mlx)
{
	int		i;
	int		j;

	i = -1;
	while (++i < ml_mlx->map->height)
	{
		j = -1;
		while (++j < ml_mlx->map->width && ml_mlx->map->map[i][j])
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

void	ml_mlx_init(t_vars *ml_mlx)
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
