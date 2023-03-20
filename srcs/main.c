/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:01:26 by yim               #+#    #+#             */
/*   Updated: 2023/03/20 15:24:33 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_error(char *str, int i)
{
	printf("Error\n");
	printf("%s\n", str);
	return (1);
}

void	exit_error(char *str, int i)
{
	printf("Error\n");
	printf("%s\n", str);
	exit (i);
}

int	map_parsing(char *filename, t_map *map)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		exit_error("file open error\n", 1);
}

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
		return (print_error("argc error", 1));
	if (map_parsing(argv[1], map))
		return (print_error("map_parsing error", 1));
}
