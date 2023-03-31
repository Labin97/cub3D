/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:18:31 by yim               #+#    #+#             */
/*   Updated: 2023/03/31 14:32:36 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	projection_height(t_projection *projection)
{
	projection->line_height = (int)(SCREEN_HEIGHT / \
	projection->perp_wall_dist);
	projection->draw_start = -(projection->line_height) / 2 + \
	SCREEN_HEIGHT / 2;
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
