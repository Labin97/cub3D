/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:46:42 by yim               #+#    #+#             */
/*   Updated: 2023/03/22 12:26:31 by yim              ###   ########.fr       */
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
	// free_all();
	exit (i);
}

void	exit_line_error(char *str, int i, char *line)
{
	if (line)
		free (line);
	printf("Error\n");
	printf("%s\n", str);
	// free_all();
	exit (i);
}
