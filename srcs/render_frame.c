/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:29:01 by yim               #+#    #+#             */
/*   Updated: 2023/03/30 19:43:07 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		project_once(vars, &vars->player);
		if (fabs(vars->player.rotation) >= 6.283185)
			vars->player.rotation = 0;
	}
	return (0);
}
