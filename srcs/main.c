/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:01:26 by yim               #+#    #+#             */
/*   Updated: 2023/03/29 16:07:13 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_leaks(void)
{
	system("leaks cub3D");
}

//print_struct check 후 제거
int	main(int argc, char **argv)
{
	t_map	map;

	// atexit(check_leaks);
	if (argc != 2)
		return (print_error("argc error", 1));
	map_parsing(argv[1], &map);
	free_all(&map);
}
