/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:01:26 by yim               #+#    #+#             */
/*   Updated: 2023/03/21 16:10:03 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(char **line)
{
	int	color;

	return (1);
}

void	init_color(t_map *map, char *line)
{
	int	r;
	int	g;
	int	b;

	line += 1;
	while (*line == ' ')
		line++;
	r = get_color(&line);
	g = get_color(&line);
	b = get_color(&line);
	if (!ft_strncmp(line, "F ", 2))
		map->floor = (r << 16 | g << 8 | b);
	if (!ft_strncmp(line, "C ", 2))
		map->ceiling = (r << 16 | g << 8 | b);
}

void	init_mapfile(t_map *map, char *line)
{
	int	i;

	if (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || \
		!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3))
		init_texture(map, line);
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
		init_color(map, line);
	// i = 0;
	// while (line[i] == ' ')
	// 	i++;
	// if (line[i] == '0' || line[i] == '1')
	// {
	// 	if (!map->no_path || !map->so_path || !map->we_path || !map->ea_path
	// 		|| (map->floor == -1) || (map->ceiling == -1))
	// 		exit_error("something wrong before map", 1);
	// 	// init_map(map, line);
	// }
}

void	print_map(t_map *map)
{
	printf("NO path = %s", map->no_path);
	printf("SO path = %s", map->so_path);
	printf("WE path = %s", map->we_path);
	printf("EA path = %s", map->ea_path);
	printf("ceiling = %d\n", map->ceiling);
	printf("floor = %d\n", map->floor);
}

void	map_parsing(char *filename, t_map *map)
{
	char	*line;
	int		fd;

	init_t_map(map);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("file open error\n", 1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			free(line);
			break ;
		}
		init_mapfile(map, line);
		free(line);
	}
	print_map(map);
	close(fd);
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		return (print_error("argc error", 1));
	map_parsing(argv[1], &map);
}
