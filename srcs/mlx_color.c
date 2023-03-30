/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:22:19 by yim               #+#    #+#             */
/*   Updated: 2023/03/30 19:22:38 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
