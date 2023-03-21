/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:53:12 by yim               #+#    #+#             */
/*   Updated: 2023/03/21 19:28:16 by yim              ###   ########.fr       */
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
	int		floor;
	int		ceiling;
	int		height;
	int		check_player;
	int		width;
	int		start;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
}	t_map;

// error
int		print_error(char *str, int i);
void	exit_error(char *str, int i);

//map_parsing
void	map_parsing(char *filename, t_map *map);

// init_mapfile
void	init_texture(t_map *map, char *line);
int		skip_space(char *line, char **tmp);
void	init_color(t_map *map, char *line, char c);
void	check_digit(char *line);
int		get_color(char **line);
void	init_map(t_map *map, char *line, int count);

#endif