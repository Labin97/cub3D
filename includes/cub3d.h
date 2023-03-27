/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:53:12 by yim               #+#    #+#             */
/*   Updated: 2023/03/23 15:33:44 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_map
{
	int		width;
	int		height;
	int		floor;
	int		ceiling;
	int		start;
	int		check_player;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	**map;
}	t_map;

// error
int		print_error(char *str, int i);
void	exit_error(char *str, int i, t_map *map);
void	exit_line_error(char *str, int i, char *line, t_map *map);
void	free_all(t_map *map);

//map_parsing
void	map_parsing(char *filename, t_map *map);

// init_texture
void	init_texture(t_map *map, char *line);

// init_color
void	init_color(t_map *map, char *line, char c);

// init_map
void	init_map(t_map *map, char *line, int count);
void	make_map(t_map *map, char *filename, int fd);
void	check_surround_wall(t_map *map);

#endif