/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 17:00:24 by yim               #+#    #+#             */
/*   Updated: 2023/03/22 17:29:07y yim              ###   ########.fr       */
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
	int	i;

	printf("NO path = %s\n", map->no_path);
	printf("SO path = %s\n", map->so_path);
	printf("WE path = %s\n", map->we_path);
	printf("EA path = %s\n", map->ea_path);
	printf("ceiling = %d\n", map->ceiling);
	printf("floor = %d\n", map->floor);
	printf("height = %d\n", map->height);
	printf("width = %d\n", map->width);
	printf("start = %d\n", map->start);
	i = 0;
	while (map->map[i])
	{
		printf("map = %s\n", map->map[i]);
		i++;
	}
}

void	check_map(t_map *map, int count, char *filename)
{
	if (map->check_player == 0)
		exit_error("player error", 1, map);
	// if (map->height != count - map->start)
	// 	exit_error("map line blank error", 1, map);
	make_map(map, filename);
	check_surround_wall(map);
}

void	init_mapfile(t_map *map, char *line, int count)
{
	int	i;

	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || \
		!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		init_texture(map, line);
	else if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		init_color(map, line, line[0]);
	else
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] == '0' || line[i] == '1')
		{
			if (!map->no_path || !map->so_path || !map->we_path || !map->ea_path
				|| (map->floor == -1) || (map->ceiling == -1))
				exit_line_error("something wrong before map", 1, line, map);
			init_map(map, line, count);
		}
		else if (line[i] != '\0')
			exit_line_error("something wrong in map", 1, line, map);
	}
}

void	check_filename(char *filename, t_map *map)
{
	char	*str;

	str = ft_strrchr(filename, '.');
	if (!str)
		exit_error("filename error", 1, map);
	if (ft_strcmp(str, ".cub"))
		exit_error("filename error", 1, map);
}

void	map_parsing(char *filename, t_map *map)
{
	char	*line;
	int		fd;
	int		count;

	init_t_map(map);
	check_filename(filename, map);
	fd = open(filename, O_RDONLY);
	if (fd < 0 || read(fd, NULL, 0) < 0)
		exit_error("file open error", 1, map);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		init_mapfile(map, line, count);
		count++;
		free(line);
	}
	check_map(map, count, filename);
	print_struct(map);
	close(fd);
}
