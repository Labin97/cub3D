/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 19:13:30 by yim               #+#    #+#             */
/*   Updated: 2023/03/31 14:04:57 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_loading2(t_vars *ml_mlx)
{
	ml_mlx->tex.e.img = mlx_xpm_file_to_image(ml_mlx->mlx, \
	ml_mlx->map->ea_path, &ml_mlx->tex.e_width, &ml_mlx->tex.e_height);
	if (ml_mlx->tex.e.img == 0)
		exit_error("texture error", 1, ml_mlx->map);
	ml_mlx->tex.e.addr = mlx_get_data_addr(ml_mlx->tex.e.img, \
	&ml_mlx->tex.e.bits_per_pixel, &ml_mlx->tex.e.line_length, \
	&ml_mlx->tex.e.endian);
	ml_mlx->tex.w.img = mlx_xpm_file_to_image(ml_mlx->mlx, \
	ml_mlx->map->we_path, &ml_mlx->tex.w_width, &ml_mlx->tex.w_height);
	if (ml_mlx->tex.w.img == 0)
		exit_error("texture error", 1, ml_mlx->map);
	ml_mlx->tex.w.addr = mlx_get_data_addr(ml_mlx->tex.w.img, \
	&ml_mlx->tex.w.bits_per_pixel, &ml_mlx->tex.w.line_length, \
	&ml_mlx->tex.w.endian);
}

void	texture_loading(t_vars *ml_mlx)
{
	ml_mlx->tex.n.img = 0;
	ml_mlx->tex.s.img = 0;
	ml_mlx->tex.e.img = 0;
	ml_mlx->tex.w.img = 0;
	ml_mlx->tex.n.img = mlx_xpm_file_to_image(ml_mlx->mlx, \
	ml_mlx->map->no_path, &ml_mlx->tex.n_width, &ml_mlx->tex.n_height);
	if (ml_mlx->tex.n.img == 0)
		exit_error("texture error", 1, ml_mlx->map);
	ml_mlx->tex.n.addr = mlx_get_data_addr(ml_mlx->tex.n.img, \
	&ml_mlx->tex.n.bits_per_pixel, &ml_mlx->tex.n.line_length, \
	&ml_mlx->tex.n.endian);
	ml_mlx->tex.s.img = mlx_xpm_file_to_image(ml_mlx->mlx, \
	ml_mlx->map->so_path, &ml_mlx->tex.s_width, &ml_mlx->tex.s_height);
	if (ml_mlx->tex.s.img == 0)
		exit_error("texture error", 1, ml_mlx->map);
	ml_mlx->tex.s.addr = mlx_get_data_addr(ml_mlx->tex.s.img, \
	&ml_mlx->tex.s.bits_per_pixel, &ml_mlx->tex.s.line_length, \
	&ml_mlx->tex.s.endian);
	texture_loading2(ml_mlx);
}

void	texture_set(t_vars *ml_mlx)
{
	texture_loading(ml_mlx);
}
