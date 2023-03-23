/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 16:59:58 by yim               #+#    #+#             */
/*   Updated: 2023/03/23 13:54:17 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_blank_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] != '0' && line[i] != '1')
		return (1);
	return (0);
}

void	make_map(t_map *map, char *filename, int fd)
{
	char	*line;
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line[ft_strlen(line) - 1] = '\0';
		if (count >= map->start && map->height > i)
		{
			if (check_blank_line(line))
				exit_line_error("line blank error", 1, line, map);
			map->map[i] = ft_strdup(line);
			if (map->map[i] == NULL)
				exit_line_error("malloc error", 1, line, map);
			i++;
		}
		count++;
		free(line);
	}
}

void	check_surround_wall2(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S' || \
				map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				if (i == 0 || j == 0)
					exit_error("surround wall error", 1, map);
				else if (i == map->height - 1 || map->map[i][j + 1] == '\0')
					exit_error("surround wall error", 1, map);
				else if (map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' ')
					exit_error("surround wall error", 1, map);
				else if (map->map[i + 1][j] == ' ' || map->map[i - 1][j] == ' ')
					exit_error("surround wall error", 1, map);
			}
			j++;
		}
		i++;
	}
}

void	check_surround_wall(t_map *map)
{
	int		i;
	int		j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == '0')
			{
				if (i == 0 || j == 0)
					exit_error("surround wall error", 1, map);
				else if (i == map->height - 1 || map->map[i][j + 1] == '\0')
					exit_error("surround wall error", 1, map);
				else if (map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' ')
					exit_error("surround wall error", 1, map);
				else if (map->map[i + 1][j] == ' ' || map->map[i - 1][j] == ' ')
					exit_error("surround wall error", 1, map);
			}
			j++;
		}
		i++;
	}
	check_surround_wall2(map);
}

void	init_map(t_map *map, char *line, int count)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && \
			line[i] != ' ' && line[i] != 'N' && line[i] != 'S' && \
			line[i] != 'E' && line[i] != 'W')
			exit_line_error("map error", 1, line, map);
		if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E' && \
			line[i] == 'W' ) && map->check_player == 1)
			exit_line_error("map error", 1, line, map);
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
