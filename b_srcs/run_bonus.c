/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:33:01 by minsulee          #+#    #+#             */
/*   Updated: 2023/03/31 14:32:43 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	destroy(t_vars *vars)
{
	free_all(vars->map);
	mlx_destroy_image(vars->mlx, vars->tex.n.img);
	mlx_destroy_image(vars->mlx, vars->tex.e.img);
	mlx_destroy_image(vars->mlx, vars->tex.s.img);
	mlx_destroy_image(vars->mlx, vars->tex.w.img);
	mlx_destroy_image(vars->mlx, vars->data.img);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_vars	ml_mlx;

	if (argc != 2)
		return (print_error("argument error", 1));
	map_parsing(argv[1], &map);
	ml_mlx.map = &map;
	ml_mlx_init(&ml_mlx);
	texture_set(&ml_mlx);
	project_once(&ml_mlx, &ml_mlx.player);
	mlx_hook(ml_mlx.win, 2, 1L << 0, key_press_hook, &ml_mlx);
	mlx_hook(ml_mlx.win, 3, 1L << 1, key_release_hook, &ml_mlx);
	mlx_hook(ml_mlx.win, 17, 0, destroy, &ml_mlx);
	mlx_loop_hook(ml_mlx.mlx, render_next_frame, &ml_mlx);
	mlx_loop(ml_mlx.mlx);
}
