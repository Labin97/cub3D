/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_color_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:48:37 by yim               #+#    #+#             */
/*   Updated: 2023/03/22 16:23:28 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_digit(char *line, t_map *map)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	if (!ft_isdigit(line[0]))
		exit_line_error("color digit error", 1, line, map);
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
			exit_line_error("color digit error", 1, line, map);
		i++;
	}
	if (comma != 2)
		exit_line_error("color num error", 1, line, map);
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
	int		r;
	int		g;
	int		b;
	char	*current;

	current = line;
	if ((map->floor != -1 && c == 'F') || (map->ceiling != -1 && c == 'C'))
		exit_line_error("color double error", 1, line, map);
	current += 1;
	while (*current == ' ')
		current++;
	check_digit(current, map);
	r = get_color(&current);
	g = get_color(&current);
	b = get_color(&current);
	if (r >= 256 || r < 0 || g >= 256 || g < 0 || b >= 256 || b < 0)
		exit_line_error("color range error", 1, line, map);
	if (c == 'F')
		map->floor = (r << 16 | g << 8 | b);
	if (c == 'C')
		map->ceiling = (r << 16 | g << 8 | b);
}
