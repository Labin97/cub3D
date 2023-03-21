/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:53:12 by yim               #+#    #+#             */
/*   Updated: 2023/03/21 15:46:16 by yim              ###   ########.fr       */
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
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
}	t_map;

// error
int		print_error(char *str, int i);
void	exit_error(char *str, int i);

// init_map
void	init_t_map(t_map *map);
int		skip_space(char *line, char **tmp);
void	init_texture(t_map *map, char *line);

#endif