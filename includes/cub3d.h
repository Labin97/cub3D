/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 14:53:12 by yim               #+#    #+#             */
/*   Updated: 2023/03/20 15:25:20 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

typedef struct s_map
{
	int		r_x;
	int		r_y;
	int		f_r;
	int		f_g;
	int		f_b;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_map;

#endif