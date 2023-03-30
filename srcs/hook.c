/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:27:29 by yim               #+#    #+#             */
/*   Updated: 2023/03/30 19:37:45 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press_hook(int key, t_vars *vars)
{
	if (key == 53)
		destroy(vars);
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

int	key_release_hook(int key, t_vars *vars)
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
