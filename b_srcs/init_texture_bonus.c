/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 16:22:59 by yim               #+#    #+#             */
/*   Updated: 2023/03/31 14:32:19 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	skip_space(char *line, char **tmp, t_map *map)
{
	int		fd;
	char	*current;

	current = line;
	current += 2;
	while (*current == ' ')
		current++;
	fd = open(current, O_RDONLY);
	if (fd < 0)
		exit_line_error("texture open error", 1, line, map);
	else
		close(fd);
	*tmp = ft_strdup(current);
	if (*tmp == NULL)
		exit_line_error("malloc error", 1, line, map);
	return (1);
}

void	check_texture_double(t_map *map, char *line)
{
	if (!ft_strncmp(line, "NO ", 3) && map->no_path != NULL)
		exit_line_error("path double error", 1, line, map);
	if (!ft_strncmp(line, "SO ", 3) && map->so_path != NULL)
		exit_line_error("path double error", 1, line, map);
	if (!ft_strncmp(line, "WE ", 3) && map->we_path != NULL)
		exit_line_error("path double error", 1, line, map);
	if (!ft_strncmp(line, "EA ", 3) && map->ea_path != NULL)
		exit_line_error("path double error", 1, line, map);
}

void	init_texture(t_map *map, char *line)
{
	char	*tmp;

	check_texture_double(map, line);
	if (!ft_strncmp(line, "NO ", 3))
	{
		if (skip_space(line, &tmp, map))
			map->no_path = tmp;
	}
	if (!ft_strncmp(line, "SO ", 3))
	{
		if (skip_space(line, &tmp, map))
			map->so_path = tmp;
	}
	if (!ft_strncmp(line, "WE ", 3))
	{
		if (skip_space(line, &tmp, map))
			map->we_path = tmp;
	}
	if (!ft_strncmp(line, "EA ", 3))
	{
		if (skip_space(line, &tmp, map))
			map->ea_path = tmp;
	}
}
