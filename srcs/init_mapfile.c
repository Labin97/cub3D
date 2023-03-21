/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mapfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:48:37 by yim               #+#    #+#             */
/*   Updated: 2023/03/21 19:53:28 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	check_digit(char *line)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	if (!ft_isdigit(line[0]))
		exit_error("color digit error", 1);
	while (line[i])
	{
		if (line[i] == ',')
		{
			i++;
			comma++;
			while (line[i] == ' ')
				i++;
		}
		if (!ft_isdigit(line[i]))
			exit_error("color digit error", 1);
		i++;
	}
	if (comma != 2)
		exit_error("color num error", 1);
}

int	get_color(char **line)
{
	int	color;

	color = ft_atoi(*line);
	while (**line != ',')
	{
		if (**line == '\0')
			break ;
		(*line)++;
	}
	(*line)++;
	return (color);
}

void	init_color(t_map *map, char *line, char c)
{
	int	r;
	int	g;
	int	b;

	line += 1;
	while (*line == ' ')
		line++;
	check_digit(line);
	r = get_color(&line);
	g = get_color(&line);
	b = get_color(&line);
	if (r >= 256 || r < 0 || g >= 256 || g < 0 || b >= 256 || b < 0)
		exit_error("color range error", 1);
	if (c == 'F')
		map->floor = (r << 16 | g << 8 | b);
	if (c == 'C')
		map->ceiling = (r << 16 | g << 8 | b);
}
