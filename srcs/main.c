/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:01:26 by yim               #+#    #+#             */
/*   Updated: 2023/03/22 15:41:13 by yim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_leaks(void)
{
	system("leaks cub3D");
}

//map line blank seg
//맨 밑에 마지막거 못 읽는거
//맨 밑에 0들어갔을 때 seg오류
//F나 C가 또 나올 경우
//NO SO도 또 나올 경우 갱신됨(leak 생김)
//line double free 체크
//중간에 숫자 아닌 이상한 문자일 경우 에러 처리
int	main(int argc, char **argv)
{
	t_map	map;

	// atexit(check_leaks);
	if (argc != 2)
		return (print_error("argc error", 1));
	map_parsing(argv[1], &map);
	free_all(&map);
}
