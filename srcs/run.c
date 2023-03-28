/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:33:01 by minsulee          #+#    #+#             */
/*   Updated: 2023/03/28 16:29:54 by minsulee         ###   ########.fr       */
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

// typedef struct s_signal
// {
// 	int signal;
// 	// char left;
// 	// char right;
// 	// char up;
// 	// char down;
// } t_signal;

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

typedef struct s_tex
{
	// void	*n;
	int		n_width;
	int		n_height;
	t_data	n;

	// void	*s;
	int		s_width;
	int		s_height;
	t_data	s;

	// void	*e;
	int		e_width;
	int		e_height;
	t_data	e;

	// void	*w;
	int		w_width;
	int		w_height;
	t_data	w;
} t_tex;

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
	int				keys;
	t_tex			*tex;
	// int				signal;

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

	// printf("PROJECT ONCE\n");

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
		// cameraX = 2 * (x + 1) / (double)SCREEN_WIDTH - 1;
		cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
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


		// double wall_distance;
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
			if (worldMap[mapX][mapY] > 0) // FIX IT TO mapY mapX. IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!
				hit = 1;
		} 


		double perpWallDist;
		if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);

		// if (side == 0)
		// 	perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		// else
		// 	perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;



		//Calculate height of line to draw on screen
		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if(drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;

			// printf("PROJECT COLOR\n");

		int	color;
		// if (side == 1)
		// {
		// 	if (stepY < 0) //west
		// 		// side = 0;
		// 		color = 0x770000; // west
		// 	else //east
		// 		// side = 1;
		// 		color = 0x007700; // east
		// }
		// else
		// {
		// 	if (stepX < 0) //north
		// 		// side = 2;
		// 		color = 0x444444; // north
		// 	else //south
		// 		// side = 3;
		// 		color = 0x000077; // south
		// }

		if (side == 1) // west east
		{
			// color = 0xFFFFFF;
			if (stepY < 0) //west
				side = 0;
			else //east
				side = 1;
		}
		else // north south, side == 0
		{
			// color = 0x444444;
			if (stepX < 0) //north
				side = 2;
			else //south
				side = 3;
		}


		double wallX; //exact value where the wall was hit.
		if (side >= 2)
			wallX = posY + perpWallDist * rayDirY;
		else
			wallX = posX + perpWallDist * rayDirX;
		if (x == SCREEN_WIDTH / 2)
			printf("side : %d, previous WallX : %f, ", side, wallX);
		wallX -= floor(wallX);



		//x coordinate on the texture
		double		texWidth;
		double		texHeight;
		// char		*texture;
		int			*texture;
		if (side == 0)
		{
			// texture = (char *)ml_mlx->tex->w.addr;
			texture = (int *)ml_mlx->tex->w.addr;
			texWidth = ml_mlx->tex->w_width;
			texHeight = ml_mlx->tex->w_height;
		}
		else if (side == 1)
		{
			// texture = (char *)ml_mlx->tex->e.addr;
			texture = (int *)ml_mlx->tex->e.addr;
			texWidth = ml_mlx->tex->e_width;
			texHeight = ml_mlx->tex->e_height;
		}
		else if (side == 2)
		{
			// texture = (char *)ml_mlx->tex->n.addr;
			texture = (int *)ml_mlx->tex->n.addr;
			texWidth = ml_mlx->tex->n_width;
			texHeight = ml_mlx->tex->n_height;
		}
		else if (side == 3)
		{
			// texture = (char *)ml_mlx->tex->s.addr;
			texture = (int *)ml_mlx->tex->s.addr;
			texWidth = ml_mlx->tex->s_width;
			texHeight = ml_mlx->tex->s_height;
		}

		//temporary
		// texWidth = 64;
		// texHeight = 64;



		int	texX = (int)(wallX * texWidth);
		if (side == 3 || side == 0)
			texX = texWidth - texX - 1;
			// texX = texWidth - texX;
		if (x == SCREEN_WIDTH / 2)
		{
			printf("posX : %f, posY : %f, rayDirX : %f, rayDirY : %f, perpWallDist : %f, WallX : %f, TEXWIDTH : %f, texX : %d\n", posX, posY, rayDirX, rayDirY, perpWallDist, wallX, texWidth, texX);
			// printf")
		}


		// printf("successfully put a pixel at %d %d\n", x, y);
		double step = 1.0 * texHeight / lineHeight;
		double texPos = (drawStart - (SCREEN_HEIGHT / 2) + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			int texY = (int)(texPos) & (int)(texHeight - 1);
			texPos += step;
			// if ((int)texHeight * texY + texX >= 0)
			color = texture[(int)texWidth * texY + texX];
			// color = texture[(int)texHeight * texY + texX];
			// HEIGHT?? WIDTH??


			// if (x == SCREEN_WIDTH / 2)
			// 	printf("%d\n", texX);
			// else
			// 	color = texture[0];
			// printf("y : %d, color : %d\n", y, color);
			// color = texture[64 * (int)texWidth + 64];
			// color = 0xFFFFFF;
			ml_mlx_put_pixel(&ml_mlx->data, x, y, color);
		}
		// exit (0);




		// ml_mlx_draw_line(&ml_mlx->data, x, drawStart, drawEnd, color);

		x++;
	}
	// usleep(100);













	mlx_put_image_to_window(ml_mlx->mlx, ml_mlx->win, ml_mlx->data.img, 0, 0);
	return (0);
}




static void	ml_mlx_init(t_vars *ml_mlx)
{
	ml_mlx->mlx = mlx_init();
	ml_mlx->win = mlx_new_window(ml_mlx->mlx, \
	SCREEN_WIDTH, SCREEN_HEIGHT, "minsulyim_cub3D");
	ml_mlx->data.img = mlx_new_image(ml_mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	ml_mlx->data.addr = mlx_get_data_addr(ml_mlx->data.img, \
		&(ml_mlx->data.bits_per_pixel), &(ml_mlx->data.line_length), \
		&(ml_mlx->data.endian));
	// ml_mlx->width = 0;
	// ml_mlx->height = 0;
	// ml_mlx->scale = 1;
}





























// int	key_hook(int key, t_vars *vars)
// {
// 	printf("key :: %d\n", key);

// 	if (key == 53)
// 		exit(0);

// 	if (key == 2) // left
// 	{
// 		// vars->player->rotation -= 1;
// 		vars->player->rotation -= M_PI / 36;

// 		double rotation = vars->player->rotation;
// 		// double oldDirX = vars->player->dirX;
// 		// double oldDirY = vars->player->dirY;
// 		double oldDirX = -1;
// 		double oldDirY = 0;
// 		vars->player->dirX = oldDirX * cos(rotation) - oldDirY * sin(rotation);
// 		vars->player->dirY = oldDirX * sin(rotation) + oldDirY * cos(rotation);
// 		// double oldPlaneX = vars->player->planeX;
// 		// double oldPlaneY = vars->player->planeY;
// 		double oldPlaneX = 0;
// 		double oldPlaneY = 1;
// 		vars->player->planeX = oldPlaneX * cos(rotation) - oldPlaneY * sin(rotation);
// 		vars->player->planeY = oldPlaneX * sin(rotation) + oldPlaneY * cos(rotation);
// 	}
// 	else if (key == 13) // up
// 	{
// 		if(worldMap[(int)(vars->player->posX + vars->player->dirX / 2)][(int)(vars->player->posY)] == 0)
// 			vars->player->posX += (vars->player->dirX / 2);
// 		if(worldMap[(int)(vars->player->posX)][(int)(vars->player->posY + vars->player->dirY / 2)] == 0)
// 			vars->player->posY += (vars->player->dirY / 2);
// 	}
// 	else if (key == 0) // right
// 	{
// 		// vars->player->rotation += 1;
// 		vars->player->rotation += M_PI / 36;

// 		double rotation = vars->player->rotation;
// 		// double oldDirX = vars->player->dirX;
// 		// double oldDirY = vars->player->dirY;
// 		double oldDirX = -1;
// 		double oldDirY = 0;
// 		vars->player->dirX = oldDirX * cos(rotation) - oldDirY * sin(rotation);
// 		vars->player->dirY = oldDirX * sin(rotation) + oldDirY * cos(rotation);
// 		// double oldPlaneX = vars->player->planeX;
// 		// double oldPlaneY = vars->player->planeY;
// 		double oldPlaneX = 0;
// 		double oldPlaneY = 1;
// 		vars->player->planeX = oldPlaneX * cos(rotation) - oldPlaneY * sin(rotation);
// 		vars->player->planeY = oldPlaneX * sin(rotation) + oldPlaneY * cos(rotation);
// 	}
// 	else if (key == 1) // down;
// 	{
// 		if(worldMap[(int)(vars->player->posX - vars->player->dirX / 2)][(int)(vars->player->posY)] == 0)
// 			vars->player->posX -= (vars->player->dirX / 2);
// 		if(worldMap[(int)(vars->player->posX)][(int)(vars->player->posY - vars->player->dirY / 2)] == 0)
// 			vars->player->posY -= (vars->player->dirY / 2);
// 	}
// 	// vars->player->rotation = vars->player->rotation % 360;
// 	project_once(vars, vars->map, vars->player);
// 	if (fabs(vars->player->rotation) >= 6.28)
// 		vars->player->rotation = 0;

// 	printf("rotation : %f\n", vars->player->rotation);
// 	// printf("posX posY : %f :: %f \n", vars->player->posX, vars->player->posY);
// 	// printf("dirX dirY : %f :: %f \n", vars->player->dirX, vars->player->dirY);
// 	// printf("planeX planeY : %f :: %f \n", vars->player->planeX, vars->player->planeY);

// 	return (1);
// }

// int	render_next_frame_help(int key, t_vars *vars)
// {
// 	printf("key :: %d\n", key);

// 	if (key == 53)
// 		exit(0);

// 	if (key == 2) // right
// 	{




// 		vars->player->rotation += M_PI / 36;

// 		double rotation = vars->player->rotation;
// 		double oldDirX = -1;
// 		double oldDirY = 0;
// 		vars->player->dirX = oldDirX * cos(rotation) - oldDirY * sin(rotation);
// 		vars->player->dirY = oldDirX * sin(rotation) + oldDirY * cos(rotation);
// 		double oldPlaneX = 0;
// 		double oldPlaneY = 1;
// 		vars->player->planeX = oldPlaneX * cos(rotation) - oldPlaneY * sin(rotation);
// 		vars->player->planeY = oldPlaneX * sin(rotation) + oldPlaneY * cos(rotation);
// 	}
// 	else if (key == 13) // up
// 	{
// 		if(worldMap[(int)(vars->player->posX + vars->player->dirX / 2)][(int)(vars->player->posY)] == 0)
// 			vars->player->posX += (vars->player->dirX / 2);
// 		if(worldMap[(int)(vars->player->posX)][(int)(vars->player->posY + vars->player->dirY / 2)] == 0)
// 			vars->player->posY += (vars->player->dirY / 2);
// 	}
// 	else if (key == 0) // left
// 	{
// 		vars->player->rotation -= M_PI / 36;

// 		double rotation = vars->player->rotation;
// 		double oldDirX = -1;
// 		double oldDirY = 0;
// 		vars->player->dirX = oldDirX * cos(rotation) - oldDirY * sin(rotation);
// 		vars->player->dirY = oldDirX * sin(rotation) + oldDirY * cos(rotation);
// 		double oldPlaneX = 0;
// 		double oldPlaneY = 1;
// 		vars->player->planeX = oldPlaneX * cos(rotation) - oldPlaneY * sin(rotation);
// 		vars->player->planeY = oldPlaneX * sin(rotation) + oldPlaneY * cos(rotation);
// 	}
// 	else if (key == 1) // down;
// 	{
// 		if(worldMap[(int)(vars->player->posX - vars->player->dirX / 2)][(int)(vars->player->posY)] == 0)
// 			vars->player->posX -= (vars->player->dirX / 2);
// 		if(worldMap[(int)(vars->player->posX)][(int)(vars->player->posY - vars->player->dirY / 2)] == 0)
// 			vars->player->posY -= (vars->player->dirY / 2);
// 	}
// 	project_once(vars, vars->map, vars->player);
// 	if (fabs(vars->player->rotation) >= 6.28)
// 		vars->player->rotation = 0;

// 	printf("rotation : %f\n", vars->player->rotation);
// 	return (1);
// }

int	key_press_hook(int key, t_vars *vars)
{
	// printf("key press:: %d\n", key);
	if (key == 53)
		exit(0);
	else if (key == 13 && !(vars->keys & 0x8)) // up
		vars->keys += 8;
	else if (key == 0 && !(vars->keys & 0x4)) // left
		vars->keys += 4;
	else if (key == 1 && !(vars->keys & 0x2)) // down
		vars->keys += 2;
	else if (key == 2 && !(vars->keys & 0x1)) // right
		vars->keys += 1;
	return (0);
}

int key_release_hook(int key, t_vars *vars)
{
	// printf("key release:: %d\n", key);
	if (key == 13 && (vars->keys & 0x8)) // up
		vars->keys -= 8;
	else if (key == 0 && (vars->keys & 0x4)) // left
		vars->keys -= 4;
	else if (key == 1 && (vars->keys & 0x2)) // down
		vars->keys -= 2;
	else if (key == 2 && (vars->keys & 0x1)) // right
		vars->keys -= 1;
	return (0);
}

void leak_check(void)
{
	system("leaks cub3D");
}


int	render_next_frame(t_vars *vars)
{
	if (vars->keys)
	{
		if (!((vars->keys & 0x8) && (vars->keys & 0x2)))
		{
			if (vars->keys & 0x8) // up
			{
				if(worldMap[(int)(vars->player->posX + vars->player->dirX / 8)][(int)(vars->player->posY)] == 0)
					vars->player->posX += (vars->player->dirX / 8);
				if(worldMap[(int)(vars->player->posX)][(int)(vars->player->posY + vars->player->dirY / 8)] == 0)
					vars->player->posY += (vars->player->dirY / 8);
			}
			else if (vars->keys & 0x2) // down
			{
				if(worldMap[(int)(vars->player->posX - vars->player->dirX / 8)][(int)(vars->player->posY)] == 0)
					vars->player->posX -= (vars->player->dirX / 8);
				if(worldMap[(int)(vars->player->posX)][(int)(vars->player->posY - vars->player->dirY / 8)] == 0)
					vars->player->posY -= (vars->player->dirY / 8);
			}
		}
		if (!((vars->keys & 0x4) && (vars->keys & 0x1)))
		{
			if (vars->keys & 0x4) // left
			{
				vars->player->rotation += M_PI / 72;

				double rotation = vars->player->rotation;
				double oldDirX = -1;
				double oldDirY = 0;
				vars->player->dirX = oldDirX * cos(rotation) - oldDirY * sin(rotation);
				vars->player->dirY = oldDirX * sin(rotation) + oldDirY * cos(rotation);
				double oldPlaneX = 0;
				double oldPlaneY = 1;
				vars->player->planeX = oldPlaneX * cos(rotation) - oldPlaneY * sin(rotation);
				vars->player->planeY = oldPlaneX * sin(rotation) + oldPlaneY * cos(rotation);
			}
			else if (vars->keys & 0x1) // right
			{
				vars->player->rotation -= M_PI / 72;

				double rotation = vars->player->rotation;
				double oldDirX = -1;
				double oldDirY = 0;
				vars->player->dirX = oldDirX * cos(rotation) - oldDirY * sin(rotation);
				vars->player->dirY = oldDirX * sin(rotation) + oldDirY * cos(rotation);
				double oldPlaneX = 0;
				double oldPlaneY = 1;
				vars->player->planeX = oldPlaneX * cos(rotation) - oldPlaneY * sin(rotation);
				vars->player->planeY = oldPlaneX * sin(rotation) + oldPlaneY * cos(rotation);
			}
		}

	}
	project_once(vars, vars->map, vars->player);
	if (fabs(vars->player->rotation) >= 6.28)
		vars->player->rotation = 0;
	return (0);
}

int main(int argc, char **argv)
{
	t_map	map;

	// atexit(leak_check);

	
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

	// printf("INIT PART\n");

	t_tex texture;
	// printf("T_TEX\n");
	texture.n.img = 0;
	// printf("TRY: FILE OPEN\n");
	texture.n.img = mlx_xpm_file_to_image(ml_mlx.mlx, "/Users/minsulee/Desktop/cub3d/cub3D/srcs/OIP.xpm", &texture.n_width, &texture.n_height);
	// printf("FILE OPEN\n");
	texture.n.addr = 0;
	texture.n.addr = mlx_get_data_addr(texture.n.img, &texture.n.bits_per_pixel, &texture.n.line_length, &texture.n.endian);

	printf("%p %p\n", texture.n.img, texture.n.addr);
	// printf("%d %d\n", texture.n_width, texture.n_height);

	// for (int py = 0; py < texture.n_height; py++)
	// {
	// 	for (int px = 0; px < texture.n_width; px++)
	// 	{
	// 		printf("%X ", texture.n.addr[py * texture.n_width + px]);
	// 	}
	// 	printf("\n");
	// }
	// exit (0);

	// printf("N DONE. FILE OPENED\n");
	texture.s.img = mlx_xpm_file_to_image(ml_mlx.mlx, "/Users/minsulee/Desktop/cub3d/cub3D/srcs/OIP-1.xpm", &texture.s_width, &texture.s_height);
	texture.s.addr = mlx_get_data_addr(texture.s.img, &texture.s.bits_per_pixel, &texture.s.line_length, &texture.s.endian);
	printf("%p %p\n", texture.s.img, texture.s.addr);
	printf("INIT2\n");
	texture.e.img = mlx_xpm_file_to_image(ml_mlx.mlx, "/Users/minsulee/Desktop/cub3d/cub3D/srcs/OIP-2.xpm", &texture.e_width, &texture.e_height);
	texture.e.addr = mlx_get_data_addr(texture.e.img, &texture.e.bits_per_pixel, &texture.e.line_length, &texture.e.endian);
	printf("%p %p\n", texture.e.img, texture.e.addr);
	printf("INIT3\n");
	texture.w.img = mlx_xpm_file_to_image(ml_mlx.mlx, "/Users/minsulee/Desktop/cub3d/cub3D/srcs/OIP-3.xpm", &texture.w_width, &texture.w_height);
	texture.w.addr = mlx_get_data_addr(texture.w.img, &texture.w.bits_per_pixel, &texture.w.line_length, &texture.w.endian);
	printf("%p %p\n", texture.w.img, texture.w.addr);
	printf("INIT4\n");
	ml_mlx.tex = &texture;


	printf("NOT INIT PART\n");
	// printf("rotation : %f\n", player.rotation);
	// printf("posX posY : %f :: %f \n", player.posX, player.posY);
	// printf("dirX dirY : %f :: %f \n", player.dirX, player.dirY);
	// printf("planeX planeY : %f :: %f \n", player.planeX, player.planeY);
	// t_signal ml_sign;
	// ml_mlx.keys = &ml_sign;

	// ml_sign.down = 0;
	// ml_sign.up = 0;
	// ml_sign.left = 0;
	// ml_sign.right = 0;
	// ml_sign.signal = 0;

	ml_mlx.keys = 0;
	//key hook : arrow key -> rotation + project_once;
	//key hook : on_destroy -> freeing things.
	project_once(&ml_mlx, &map, &player);
	// mlx_hook(ml_mlx.win, 2, 1L << 0, key_hook, &ml_mlx);
	mlx_hook(ml_mlx.win, 2, 1L << 0, key_press_hook, &ml_mlx);
	mlx_hook(ml_mlx.win, 3, 1L << 1, key_release_hook, &ml_mlx);
	mlx_loop_hook(ml_mlx.mlx, render_next_frame, &ml_mlx);
	mlx_loop(ml_mlx.mlx);

	// while (1)
	// {

	// }

	free_all(&map);
}