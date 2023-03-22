/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:00:24 by yim               #+#    #+#             */
/*   Updated: 2023/03/22 12:30:28 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_t_map(t_map *map)
{
	ft_memset(map, 0, sizeof(t_map));
	map->ceiling = -1;
	map->floor = -1;
}

void	print_struct(t_map *map)
{
	printf("NO path = %s\n", map->no_path);
	printf("SO path = %s\n", map->so_path);
	printf("WE path = %s\n", map->we_path);
	printf("EA path = %s\n", map->ea_path);
	printf("ceiling = %d\n", map->ceiling);
	printf("floor = %d\n", map->floor);
	printf("height = %d\n", map->height);
	printf("width = %d\n", map->width);
}

void	check_map(t_map *map, int count)
{
	if (map->check_player == 0)
		exit_error("player error", 1);
	if (map->height != count - map->start)
		exit_error("map line blank", 1);
}

void	init_mapfile(t_map *map, char *line, int count)
{
	int	i;

	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || \
		!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		init_texture(map, line);
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		init_color(map, line, line[0]);
	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '0' || line[i] == '1')
	{
		if (!map->no_path || !map->so_path || !map->we_path || !map->ea_path
			|| (map->floor == -1) || (map->ceiling == -1))
			exit_line_error("something wrong before map", 1, line);
		init_map(map, line, count);
	}
}

void	map_parsing(char *filename, t_map *map)
{
	char	*line;
	int		fd;
	int		count;

	init_t_map(map);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("file open error\n", 1);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			free(line);
			break ;
		}
		line[ft_strlen(line) - 1] = '\0';
		init_mapfile(map, line, count);
		count++;
		free(line);
	}
	check_map(map, count);
	print_struct(map);
	close(fd);
}
