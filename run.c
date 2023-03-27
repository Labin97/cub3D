/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:33:01 by minsulee          #+#    #+#             */
/*   Updated: 2023/03/27 14:31:24 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


#define mapWidth 24
#define mapHeight 24
// #define screenWidth 640
// #define screenHeight 480

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};



typedef struct s_player
{
	double	posX;
	double	posY;
	double	dirX, dirY;
	double	planeX, planeY;

	double	rotation;

} t_player;


#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080


typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	struct s_data	data;
	// double			rotate_x;
	// double			rotate_y;
	// double			rotate_z;
	// int				width;
	// int				height;
	// int				scale;
	t_player		*player;
	t_map			*map;

}				t_vars;



#include <limits.h>



void	ml_mlx_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ml_mlx_draw_line(t_data *data, int x, int drawStart, int drawEnd, int color)
{
	int index;

	index = drawStart;
	while (index <= drawEnd)
	{
		ml_mlx_put_pixel(data, x, index, color);
		index++;
	}
}

void	ml_mlx_clear_window(t_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			ml_mlx_put_pixel(&vars->data, x, y, 0x00000000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
}



int	project_once(t_vars *ml_mlx, t_map *map, t_player *player)
{

	//1. x축 -1 ~ 1 보면서 거리 계산 : 1920(window_width) 만큼 scan
	//2. 계산된 각각의 거리 저장하기
	//3. 저장된 거리에 따라 y축이 얼마나 길어야 하는지 계산
	//4. 저장된 y축 길이에 따라 mlx_win 에 x = 0 ~ window_width - 1까지 세로축 그리가
	//5. 그려진 그대로 출력 후 종료



	ml_mlx_clear_window(ml_mlx);

	double posX = player->posX;
	// posX = 22; // test
	double posY = player->posY;
	// posY = 12; // test

	int x = 0, y = 0;
	while (x < SCREEN_WIDTH)
	{
		double cameraX;
		// cameraX = (2 * (x + 1) / (double(1920)) - 1);
		cameraX = 2 * (x + 1) / (double)SCREEN_WIDTH - 1;
		double rayDirX = player->dirX + player->planeX * cameraX;
		double rayDirY = player->dirY + player->planeY * cameraX;



		double deltaDistX;// = fabs(1 / rayDirX);
		if (rayDirX == 0)
			deltaDistX = __DBL_MAX__;
		else
			deltaDistX = fabs(1 / rayDirX);
		
		double deltaDistY;// = fabs(1 / rayDirY);
		if (rayDirY == 0)
			deltaDistY = __DBL_MAX__;
		else
			deltaDistY = fabs(1 / rayDirY);


		double wall_distance;
		int hit = 0;
		int side;
		
		int mapX = (int) player->posX;
		int mapY = (int) player->posY;

		double	sideDistX;
		double	sideDistY;

		int stepX;
		int stepY;

		// int hit = 0;
		// int side;





		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}



		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		} 


		double perpWallDist;
		if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);





		//Calculate height of line to draw on screen
		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if(drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;



		int	color;
		if (side == 1)
			color = 0x87CEEB;
		else
			color = 0x444444;

		ml_mlx_draw_line(&ml_mlx->data, x, drawStart, drawEnd, color);



















		x++;
	}














	mlx_put_image_to_window(ml_mlx->mlx, ml_mlx->win, ml_mlx->data.img, 0, 0);
	return (0);
}




static void	ml_mlx_init(t_vars *ml_mlx)
{
	ml_mlx->mlx = mlx_init();
	ml_mlx->win = mlx_new_window(ml_mlx->mlx, \
	SCREEN_WIDTH, SCREEN_HEIGHT, "minsulee_fdf");
	ml_mlx->data.img = mlx_new_image(ml_mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	ml_mlx->data.addr = mlx_get_data_addr(ml_mlx->data.img, \
		&(ml_mlx->data.bits_per_pixel), &(ml_mlx->data.line_length), \
		&(ml_mlx->data.endian));
	// ml_mlx->width = 0;
	// ml_mlx->height = 0;
	// ml_mlx->scale = 1;
}





























int	key_hook(int key, t_vars *vars)
{
	printf("key :: %d\n", key);
	if (key == 2) // left
	{
		vars->player->rotation -= 1;

		double rotation = vars->player->rotation / 36;
		// double oldDirX = vars->player->dirX;
		// double oldDirY = vars->player->dirY;
		double oldDirX = -1;
		double oldDirY = 0;
		vars->player->dirX = oldDirX * cos(rotation) - oldDirY * sin(rotation);
		vars->player->dirY = oldDirX * sin(rotation) + oldDirY * cos(rotation);
		// double oldPlaneX = vars->player->planeX;
		// double oldPlaneY = vars->player->planeY;
		double oldPlaneX = 0;
		double oldPlaneY = 1;
		vars->player->planeX = oldPlaneX * cos(rotation) - oldPlaneY * sin(rotation);
		vars->player->planeY = oldPlaneX * sin(rotation) + oldPlaneY * cos(rotation);
	}
	else if (key == 13) // up
	{
		vars->player->posX += (vars->player->dirX / 1);
		vars->player->posY += (vars->player->dirY / 1);
	}
	else if (key == 0) // right
	{
		vars->player->rotation += 1;

		double rotation = vars->player->rotation / 36;
		// double oldDirX = vars->player->dirX;
		// double oldDirY = vars->player->dirY;
		double oldDirX = -1;
		double oldDirY = 0;
		vars->player->dirX = oldDirX * cos(rotation) - oldDirY * sin(rotation);
		vars->player->dirY = oldDirX * sin(rotation) + oldDirY * cos(rotation);
		// double oldPlaneX = vars->player->planeX;
		// double oldPlaneY = vars->player->planeY;
		double oldPlaneX = 0;
		double oldPlaneY = 1;
		vars->player->planeX = oldPlaneX * cos(rotation) - oldPlaneY * sin(rotation);
		vars->player->planeY = oldPlaneX * sin(rotation) + oldPlaneY * cos(rotation);
	}
	else if (key == 1) // down;
	{
		vars->player->posX -= (vars->player->dirX / 1);
		vars->player->posY -= (vars->player->dirY / 1);
	}
	// vars->player->rotation = vars->player->rotation % 360;
	project_once(vars, vars->map, vars->player);


	// printf("rotation : %f\n", vars->player->rotation);
	// printf("posX posY : %f :: %f \n", vars->player->posX, vars->player->posY);
	// printf("dirX dirY : %f :: %f \n", vars->player->dirX, vars->player->dirY);
	// printf("planeX planeY : %f :: %f \n", vars->player->planeX, vars->player->planeY);

	return (1);
}


int main(int argc, char **argv)
{
	t_map	map;

	

	
	if (argc != 2)
		return (print_error("argc error", 1));
	map_parsing(argv[1], &map);

	//1. get player info
	//2. initialize the player's info. t_player
	//3. 


	// if N, rotation = 0;
	// if E, rotation = 2*pi/4;
	// if S, rotation = pi;
	// if W, rotation = 3*pi/4;
	t_vars	ml_mlx;
	ml_mlx.map = &map;
	ml_mlx_init(&ml_mlx);
	t_player player;
	player.rotation = 0;
	player.posX = 22;
	player.posY = 12;
	player.dirX = -1;
	player.dirY = 0;
	player.planeX = 0;
	// player.planeY = 0.66;
	player.planeY = 1;
	ml_mlx.player = &player;

	// printf("rotation : %f\n", player.rotation);
	// printf("posX posY : %f :: %f \n", player.posX, player.posY);
	// printf("dirX dirY : %f :: %f \n", player.dirX, player.dirY);
	// printf("planeX planeY : %f :: %f \n", player.planeX, player.planeY);


	//key hook : arrow key -> rotation + project_once;
	//key hook : on_destroy -> freeing things.
	project_once(&ml_mlx, &map, &player);
	mlx_hook(ml_mlx.win, 2, 1L << 0, key_hook, &ml_mlx);






	mlx_loop(ml_mlx.mlx);

	// while (1)
	// {

	// }

	free_all(&map);
}