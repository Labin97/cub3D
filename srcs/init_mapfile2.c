/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mapfile2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:59:58 by yim               #+#    #+#             */
/*   Updated: 2023/03/21 19:44:21 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map(t_map *map, char *line, int count)
{
	int	i;

	i = 0;
	printf ("%s\n", line);
	while (line[i])
	{
		if (line[i] != '\n' && line[i] != '1' && line[i] != '0' && \
			line[i] != ' ' && line[i] != 'N' && line[i] != 'S' && \
			line[i] != 'E' && line[i] != 'W')
			exit_error("map error", 1);
		if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E' && \
			line[i] == 'W' ) && map->check_player == 1)
			exit_error("map error", 1);
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' && \
			line[i] == 'W')
			map->check_player = 1;
		i++;
	}
	if (map->width < i)
		map->width = i;
	map->height++;
	if (map->start == 0)
		map->start = count;
}
