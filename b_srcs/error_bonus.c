/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:46:42 by yim               #+#    #+#             */
/*   Updated: 2023/03/31 14:32:06 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	print_error(char *str, int i)
{
	printf("Error\n");
	printf("%s\n", str);
	return (i);
}

void	exit_error(char *str, int i, t_map *map)
{
	printf("Error\n");
	printf("%s\n", str);
	free_all(map);
	exit (i);
}

void	exit_line_error(char *str, int i, char *line, t_map *map)
{
	if (line)
		free (line);
	printf("Error\n");
	printf("%s\n", str);
	free_all(map);
	exit (i);
}

void	free_all(t_map *map)
{
	int	i;

	free(map->no_path);
	free(map->so_path);
	free(map->we_path);
	free(map->ea_path);
	i = 0;
	if (map->map)
	{
		while (map->map[i])
		{
			free(map->map[i]);
			i++;
		}
	}
	free(map->map);
}
