/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mapfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:48:37 by yim               #+#    #+#             */
/*   Updated: 2023/03/21 16:09:26 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_t_map(t_map *map)
{
	ft_memset(map, 0, sizeof(t_map));
	map->ceiling = -1;
	map->floor = -1;
}

int	skip_space(char *line, char **tmp)
{
	int	fd;

	line += 2;
	while (*line == ' ')
		line++;
	// fd = open(line, O_RDONLY);
	// if (fd < 0)
	// 	exit_error("texture open error", 1);
	// else
	// 	close(fd);
	*tmp = ft_strdup(line);
	return (1);
}

void	init_texture(t_map *map, char *line)
{
	char	*tmp;

	if (!ft_strncmp(line, "NO ", 3))
	{
		if (skip_space(line, &tmp))
			map->no_path = tmp;
	}
	if (!ft_strncmp(line, "SO ", 3))
	{
		if (skip_space(line, &tmp))
			map->so_path = tmp;
	}
	if (!ft_strncmp(line, "WE ", 3))
	{
		if (skip_space(line, &tmp))
			map->we_path = tmp;
	}
	if (!ft_strncmp(line, "EA ", 3))
	{
		if (skip_space(line, &tmp))
			map->ea_path = tmp;
	}
}
