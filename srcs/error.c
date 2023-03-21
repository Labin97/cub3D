/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:46:42 by yim               #+#    #+#             */
/*   Updated: 2023/03/21 15:10:28 by yim              ###   ########.fr       */
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