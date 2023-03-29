/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsulee <minsulee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:33:01 by minsulee          #+#    #+#             */
/*   Updated: 2023/03/29 15:52:07 by minsulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// #define screenWidth 640
// #define screenHeight 480

// int worldMap[mapHeight][mapWidth]=
// {
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
//   {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };



// typedef struct s_signal
// {
// 	int signal;
// 	// char left;
// 	// char right;
// 	// char up;
// 	// char down;
// } t_signal;


#include <limits.h>



void	ml_mlx_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// void	ml_mlx_draw_line(t_data *data, int x, int drawStart, int drawEnd, int color)
// {
// 	int index;

// 	index = drawStart;
// 	while (index <= drawEnd)
// 	{
// 		ml_mlx_put_pixel(data, x, index, color);
// 		index++;
// 	}
// }

// void	ml_mlx_clear_window(t_vars *vars)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < SCREEN_HEIGHT)
// 	{
// 		x = 0;
// 		while (x < SCREEN_WIDTH)
// 		{
// 			ml_mlx_put_pixel(&vars->data, x, y, 0x00000000);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(vars->mlx, vars->win, vars->data.img, 0, 0);
// }

void	ml_mlx_ceiling(t_vars *vars, int color)
{
	int	half_height;
	int y;
	int x;

	y = 0;
	x = 0;
	half_height = SCREEN_HEIGHT / 2;
	while (y < half_height)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			ml_mlx_put_pixel(&vars->data, x, y, color);
			x++;
		}
		y++;
	}
}

void	ml_mlx_floor(t_vars *vars, int color)
{
	int y;
	int x;

	y = SCREEN_HEIGHT / 2;
	x = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			ml_mlx_put_pixel(&vars->data, x, y, color);
			x++;
		}
		y++;
	}
}

typedef struct s_projection
{
	double posX;
	double posY;

	double cameraX;
	double rayDirX;
	double rayDirY;
	double deltaDistX;
	double deltaDistY;
	
	int hit;
	int side;
	
	int mapX;
	int mapY;

	double	sideDistX;
	double	sideDistY;

	int stepX;
	int stepY;

	double perpWallDist;

	double wallX;

	int lineHeight;
	int drawStart;
	int drawEnd;

	double		texWidth;
	double		texHeight;
	int			*texture;

} t_projection;











void	projection_init(t_projection *projection, int x, t_player *player)
{
	projection->cameraX = 2 * (x - 1) / (double)SCREEN_WIDTH - 1;
	projection->rayDirX = player->dirX + player->planeX * projection->cameraX;
	projection->rayDirY = player->dirY + player->planeY * projection->cameraX;
	projection->hit = 0;
	projection->side = 0;
	if (projection->rayDirX == 0)
		projection->deltaDistX = __DBL_MAX__;
	else
		projection->deltaDistX = fabs(1 / projection->rayDirX);
	
	if (projection->rayDirY == 0)
		projection->deltaDistY = __DBL_MAX__;
	else
		projection->deltaDistY = fabs(1 / projection->rayDirY);
	projection->posX = player->posX;
	projection->posY = player->posY;
	projection->mapX = (int) player->posX;
	projection->mapY = (int) player->posY;
}

void	projection_direction_set(t_projection *projection)
{
		if (projection->rayDirX < 0)
		{
			projection->stepX = -1;
			projection->sideDistX = (projection->posX - projection->mapX) * projection->deltaDistX;
		}
		else
		{
			projection->stepX = 1;
			projection->sideDistX = (projection->mapX + 1.0 - projection->posX) * projection->deltaDistX;
		}
		if (projection->rayDirY < 0)
		{
			projection->stepY = -1;
			projection->sideDistY = (projection->posY - projection->mapY) * projection->deltaDistY;
		}
		else
		{
			projection->stepY = 1;
			projection->sideDistY = (projection->mapY + 1.0 - projection->posY) * projection->deltaDistY;
		}
}

void	projection_shoot(t_map *map, t_projection *projection)
{
		int hit;

		while (projection->hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (projection->sideDistX < projection->sideDistY)
			{
				projection->sideDistX += projection->deltaDistX;
				projection->mapX += projection->stepX;
				projection->side = 0;
			}
			else
			{
				projection->sideDistY += projection->deltaDistY;
				projection->mapY += projection->stepY;
				projection->side = 1;
			}
			//Check if ray has hit a wall
			if (map->map[projection->mapY][projection->mapX] > '0') // FIX IT TO mapY mapX. IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!
				projection->hit = 1;
		}
		// double perpWallDist;
		if (projection->side == 0)
			projection->perpWallDist = (projection->sideDistX - projection->deltaDistX);
		else
			projection->perpWallDist = (projection->sideDistY - projection->deltaDistY);


//이거 원래 height 다음에 있는건데 겹치는 거 없는 것 같아서 일단 위로 데리고 왔음!
		if (projection->side == 0)
			projection->wallX = projection->posY + projection->perpWallDist * projection->rayDirY;
		else
			projection->wallX = projection->posX + projection->perpWallDist * projection->rayDirX;
		// if (x == SCREEN_WIDTH / 2)
		// 	printf("side : %d, previous WallX : %f, ", projection->side, projection->wallX);
		projection->wallX -= floor(projection->wallX);
}

void	projection_height(t_projection *projection)
{
		projection->lineHeight = (int)(SCREEN_HEIGHT / projection->perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		projection->drawStart = -(projection->lineHeight) / 2 + SCREEN_HEIGHT / 2;
		if (projection->drawStart < 0)
			projection->drawStart = 0;
		projection->drawEnd = (projection->lineHeight) / 2 + SCREEN_HEIGHT / 2;
		if (projection->drawEnd >= SCREEN_HEIGHT)
			projection->drawEnd = SCREEN_HEIGHT - 1;
}

void	projection_side(t_projection *projection)
{

	if (projection->side == 1) // west east
	{
		if (projection->stepY < 0) //west
			projection->side = 0;
		else //east
			projection->side = 1;
	}
	else // north south, side == 0
	{
		if (projection->stepX < 0) //north
			projection->side = 2;
		else //south
			projection->side = 3;
	}
}

void	projection_texture(t_tex *tex, t_projection *projection)
{
		if (projection->side == 0)
		{
			projection->texture = (int *)tex->n.addr;
			projection->texWidth = tex->n_width;
			projection->texHeight = tex->n_height;
		}
		else if (projection->side == 1)
		{
			projection->texture = (int *)tex->s.addr;
			projection->texWidth = tex->s_width;
			projection->texHeight = tex->s_height;
		}
		if (projection->side == 2)
		{
			projection->texture = (int *)tex->w.addr;
			projection->texWidth = tex->w_width;
			projection->texHeight = tex->w_height;
		}
		else if (projection->side == 3)
		{
			projection->texture = (int *)tex->e.addr;
			projection->texWidth = tex->e_width;
			projection->texHeight = tex->e_height;
		}
}

void	projection_draw(t_vars *ml_mlx, t_projection *projection, int x)
{
		int	texX;
		int texY;
		texX = (int)(projection->wallX * projection->texWidth);
		if (x == SCREEN_WIDTH / 2)
		{
			printf("posX : %f, posY : %f, rayDirX : %f, rayDirY : %f, perpWallDist : %f, WallX : %f, TEXWIDTH : %f, texX : %d\n", projection->posX, projection->posY, projection->rayDirX, projection->rayDirY, projection->perpWallDist, projection->wallX, projection->texWidth, texX);
			printf("\n");
		}
		int	color;
		double step;
		double texPos;


		if (projection->side == 3 || projection->side == 0)
			texX = projection->texWidth - texX - 1;
		step = 1.0 * projection->texHeight / projection->lineHeight;
		texPos = (projection->drawStart - (SCREEN_HEIGHT / 2) + projection->lineHeight / 2) * step;
		for (int y = projection->drawStart; y < projection->drawEnd; y++)
		{
			texY = (int)(texPos) & (int)(projection->texHeight - 1);
			texPos += step;
			color = projection->texture[(int) projection->texWidth * texY + texX];
			// ml_mlx_put_pixel(&ml_mlx->data, x, y, projection->texture[(int)projection->texWidth * texY + texX]);
			ml_mlx_put_pixel(&ml_mlx->data, x, y, color);
		}
}

int	project_once(t_vars *ml_mlx, t_map *map, t_player *player)
{

	//1. x축 -1 ~ 1 보면서 거리 계산 : 1920(window_width) 만큼 scan
	//2. 계산된 각각의 거리 저장하기
	//3. 저장된 거리에 따라 y축이 얼마나 길어야 하는지 계산
	//4. 저장된 y축 길이에 따라 mlx_win 에 x = 0 ~ window_width - 1까지 세로축 그리가
	//5. 그려진 그대로 출력 후 종료

	// printf("PROJECT ONCE\n");

	// ml_mlx_clear_window(ml_mlx);
	ml_mlx_ceiling(ml_mlx, ml_mlx->map->ceiling);
	ml_mlx_floor(ml_mlx, ml_mlx->map->floor);

	t_projection projection;
	
	char **worldMap = ml_mlx->map->map;

	double posX = player->posX;
	// posX = 22; // test
	double posY = player->posY;
	// posY = 12; // test

	int x = 0, y = 0;
	while (x < SCREEN_WIDTH)
	{
		// ft_memset(&projection, 0, sizeof(t_projection));
		projection_init(&projection, x, player);
		// double cameraX; // 여기서만 씀
		// projection.cameraX = 2 * (x - 1) / (double)SCREEN_WIDTH - 1;
		// projection.rayDirX = player->dirX + player->planeX * projection.cameraX;
		// projection.rayDirY = player->dirY + player->planeY * projection.cameraX;
		// //DEL cameraX

		// //SET HOW LONG A RAY WILL GO THROUGH X AXIS AND Y AXIS
		// // double deltaDistX;// = fabs(1 / rayDirX);
		// if (projection.rayDirX == 0)
		// 	projection.deltaDistX = __DBL_MAX__;
		// else
		// 	projection.deltaDistX = fabs(1 / projection.rayDirX);
		
		// // double projection.deltaDistY;// = fabs(1 / rayDirY);
		// if (projection.rayDirY == 0)
		// 	projection.deltaDistY = __DBL_MAX__;
		// else
		// 	projection.deltaDistY = fabs(1 / projection.rayDirY);


		// double wall_distance;
		// projection.cameraX = 2 * (x - 1) / (double)SCREEN_WIDTH - 1;
		// projection.rayDirX = player->dirX + player->planeX * projection.cameraX;
		// projection.rayDirY = player->dirY + player->planeY * projection.cameraX;
		// projection.hit = 0;
		// projection.side = 0;
		// if (projection.rayDirX == 0)
		// 	projection.deltaDistX = __DBL_MAX__;
		// 	else
		// 	projection.deltaDistX = fabs(1 / projection.rayDirX);
		
		// if (projection.rayDirY == 0)
		// 	projection.deltaDistY = __DBL_MAX__;
		// 	else
		// 	projection.deltaDistY = fabs(1 / projection.rayDirY);
		// projection.mapX = (int) player->posX;
		// projection.mapY = (int) player->posY;

















		// int hit = 0;
		// int side;

		
		// int mapX = (int) player->posX;
		// int mapY = (int) player->posY;


		// double	sideDistX;
		// double	sideDistY;

		// int stepX;
		// int stepY;

		// int hit = 0;
		// int side;




		//SET STEP AND STARTING_DISTANCE
		projection_direction_set(&projection);
		// if (rayDirX < 0)
		// {
		// 	stepX = -1;
		// 	sideDistX = (posX - mapX) * deltaDistX;
		// }
		// else
		// {
		// 	stepX = 1;
		// 	sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		// }
		// if (rayDirY < 0)
		// {
		// 	stepY = -1;
		// 	sideDistY = (posY - mapY) * deltaDistY;
		// }
		// else
		// {
		// 	stepY = 1;
		// 	sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		// }


		//SHOOT THE RAY AND SEE WHERE IT ARRIVES
		projection_shoot(ml_mlx->map, &projection);
		// while (hit == 0)
		// {
		// 	//jump to next map square, either in x-direction, or in y-direction
		// 	if (sideDistX < sideDistY)
		// 	{
		// 		sideDistX += deltaDistX;
		// 		mapX += stepX;
		// 		side = 0;
		// 	}
		// 	else
		// 	{
		// 		sideDistY += deltaDistY;
		// 		mapY += stepY;
		// 		side = 1;
		// 	}
		// 	//Check if ray has hit a wall
		// 	if (worldMap[mapY][mapX] > '0') // FIX IT TO mapY mapX. IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!
		// 		hit = 1;
		// }


		// double perpWallDist;
		// if(side == 0) perpWallDist = (sideDistX - deltaDistX);
		// else          perpWallDist = (sideDistY - deltaDistY);

		// if (side == 0)
		// 	perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		// else
		// 	perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;



		//Calculate height of line to draw on screen
		projection_height(&projection);
		// int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

		// //calculate lowest and highest pixel to fill in current stripe
		// int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		// if(drawStart < 0)
		// 	drawStart = 0;
		// int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		// if (drawEnd >= SCREEN_HEIGHT)
		// 	drawEnd = SCREEN_HEIGHT - 1;

		// projection.lineHeight = (int)(SCREEN_HEIGHT / projection.perpWallDist);

		// //calculate lowest and highest pixel to fill in current stripe
		// projection.drawStart = -projection.lineHeight / 2 + SCREEN_HEIGHT / 2;
		// if (projection.drawStart < 0)
		// 	projection.drawStart = 0;
		// projection.drawEnd = projection.lineHeight / 2 + SCREEN_HEIGHT / 2;
		// if (projection.drawEnd >= SCREEN_HEIGHT)
		// 	projection.drawEnd = SCREEN_HEIGHT - 1;
		projection_side(&projection);
		// if (side == 1) // west east
		// {
		// 	if (stepY < 0) //west
		// 		side = 0;
		// 	else //east
		// 		side = 1;
		// }
		// else // north south, side == 0
		// {
		// 	if (stepX < 0) //north
		// 		side = 2;
		// 	else //south
		// 		side = 3;
		// }


		// double wallX; //exact value where the wall was hit.
		// if (side >= 2)
		// 	wallX = posY + perpWallDist * rayDirY;
		// else
		// 	wallX = posX + perpWallDist * rayDirX;
		// // if (x == SCREEN_WIDTH / 2)
		// // 	printf("side : %d, previous WallX : %f, ", side, wallX);
		// wallX -= floor(wallX);



		//x coordinate on the texture
		// double		texWidth;
		// double		texHeight;
		// int			*texture;


		projection_texture(ml_mlx->tex, &projection);
		// if (side == 0)
		// {
		// 	texture = (int *)ml_mlx->tex->n.addr;
		// 	texWidth = ml_mlx->tex->n_width;
		// 	texHeight = ml_mlx->tex->n_height;
		// }
		// else if (side == 1)
		// {
		// 	texture = (int *)ml_mlx->tex->s.addr;
		// 	texWidth = ml_mlx->tex->s_width;
		// 	texHeight = ml_mlx->tex->s_height;
		// }
		// if (side == 2)
		// {
		// 	texture = (int *)ml_mlx->tex->w.addr;
		// 	texWidth = ml_mlx->tex->w_width;
		// 	texHeight = ml_mlx->tex->w_height;
		// }
		// else if (side == 3)
		// {
		// 	texture = (int *)ml_mlx->tex->e.addr;
		// 	texWidth = ml_mlx->tex->e_width;
		// 	texHeight = ml_mlx->tex->e_height;
		// }



		//temporary
		// texWidth = 64;
		// texHeight = 64;



		// int	texX = (int)(wallX * texWidth);
		// int texY;
		// if (side == 3 || side == 0)
		// 	texX = texWidth - texX - 1;
		// // if (x == SCREEN_WIDTH / 2)
		// // {
		// // 	// printf("posX : %f, posY : %f, rayDirX : %f, rayDirY : %f, perpWallDist : %f, WallX : %f, TEXWIDTH : %f, texX : %d\n", posX, posY, rayDirX, rayDirY, perpWallDist, wallX, texWidth, texX);
		// // 	// printf")
		// // }
		// int	color;
		// double step = 1.0 * texHeight / lineHeight;
		// double texPos = (drawStart - (SCREEN_HEIGHT / 2) + lineHeight / 2) * step;
		// for (int y = drawStart; y < drawEnd; y++)
		// {
		// 	texY = (int)(texPos) & (int)(texHeight - 1);
		// 	texPos += step;
		// 	color = texture[(int)texWidth * texY + texX];
		// 	ml_mlx_put_pixel(&ml_mlx->data, x, y, color);
		// }

		projection_draw(ml_mlx, &projection, x);


		// int	texX = (int)(projection.wallX * projection.texWidth);
		// int texY;
		// if (projection.side == 3 || projection.side == 0)
		// 	texX = projection.texWidth - texX - 1;
		// if (x == SCREEN_WIDTH / 2)
		// {
		// 	printf("posX : %f, posY : %f, rayDirX : %f, rayDirY : %f, perpWallDist : %f, WallX : %f, TEXWIDTH : %f, texX : %d\n", projection.posX, projection.posY, projection.rayDirX, projection.rayDirY, projection.perpWallDist, projection.wallX, projection.texWidth, texX);
		// 	printf("\n");
		// }
		// int	color;
		// double step = 1.0 * projection.texHeight / projection.lineHeight;
		// double texPos = (projection.drawStart - (SCREEN_HEIGHT / 2) + projection.lineHeight / 2) * step;
		// for (int y = projection.drawStart; y < projection.drawEnd; y++)
		// {
		// 	texY = (int)(texPos) & (int)(projection.texHeight - 1);
		// 	texPos += step;
		// 	color = projection.texture[(int)projection.texWidth * texY + texX];
		// 	ml_mlx_put_pixel(&ml_mlx->data, x, y, color);
		// }
		x++;
	}













	mlx_put_image_to_window(ml_mlx->mlx, ml_mlx->win, ml_mlx->data.img, 0, 0);
	return (0);
}


void	find_player_pos(t_vars *ml_mlx)
{
	int		i;
	int		j;

	i = 0;
	while (i < ml_mlx->map->height)
	{
		j = 0;
		while (j < ml_mlx->map->width)
		{
			if (ml_mlx->map->map[i][j] == 'N' || ml_mlx->map->map[i][j] == 'S' \
			|| ml_mlx->map->map[i][j] == 'W' || ml_mlx->map->map[i][j] == 'E')
			{
				ml_mlx->player->posX = j + 0.5;
				ml_mlx->player->posY = i + 0.5;
				if (ml_mlx->map->map[i][j] == 'N')
					ml_mlx->player->dirY = -1;
				else if (ml_mlx->map->map[i][j] == 'S')
					ml_mlx->player->dirY = 1;
				else if (ml_mlx->map->map[i][j] == 'W')
					ml_mlx->player->dirX = -1;
				else if (ml_mlx->map->map[i][j] == 'E')
					ml_mlx->player->dirX = 1;
			}
		}
	}
}

static void	ml_mlx_init(t_vars *ml_mlx)
{
	// ft_memset(ml_mlx, 0, sizeof(t_vars));
	ml_mlx->mlx = mlx_init();
	ml_mlx->win = mlx_new_window(ml_mlx->mlx, \
	SCREEN_WIDTH, SCREEN_HEIGHT, "minsulyim_cub3D");
	ml_mlx->data.img = mlx_new_image(ml_mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	ml_mlx->data.addr = mlx_get_data_addr(ml_mlx->data.img, \
		&(ml_mlx->data.bits_per_pixel), &(ml_mlx->data.line_length), \
		&(ml_mlx->data.endian));
	// find_player_pos(ml_mlx);
	// ml_mlx->width = 0;
	// ml_mlx->height = 0;
	// ml_mlx->scale = 1;
}







int	key_press_hook(int key, t_vars *vars)
{
	printf("key press:: %d\n", key);
	if (key == 53)
		exit(0);
	else if (key == 123 && !(vars->keys & 0x32)) // left arrow key
		vars->keys += 32;
	else if (key == 124 && !(vars->keys & 0x16)) // right arrow key
		vars->keys += 16;
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
	printf("key release:: %d\n", key);
	if (key == 123 && (vars->keys & 0x32)) // left arrow key
		vars->keys -= 32;
	else if (key == 124 && (vars->keys & 0x16)) // right arrow key
		vars->keys -= 16;
	else if (key == 13 && (vars->keys & 0x8)) // up
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

	char **worldMap = vars->map->map;
	
	if (vars->keys)
	{
		if (!((vars->keys & 0x8) && (vars->keys & 0x2)))
		{
			if (vars->keys & 0x8) // up
			{
				if(worldMap[(int)(vars->player->posY)][(int)(vars->player->posX + vars->player->dirX / 8)] == '0')
					vars->player->posX += (vars->player->dirX / 8);
				if(worldMap[(int)(vars->player->posY + vars->player->dirY / 8)][(int)(vars->player->posX)] == '0')
					vars->player->posY += (vars->player->dirY / 8);
			}
			else if (vars->keys & 0x2) // down
			{
				if(worldMap[(int)(vars->player->posY)][(int)(vars->player->posX - vars->player->dirX / 8)] == '0')
					vars->player->posX -= (vars->player->dirX / 8);
				if(worldMap[(int)(vars->player->posY - vars->player->dirY / 8)][(int)(vars->player->posX)] == '0')
					vars->player->posY -= (vars->player->dirY / 8);
			}
		}
		if (!((vars->keys & 0x4) && (vars->keys & 0x1)))
		{
			if (vars->keys & 0x4) // left
			{
				vars->player->rotation -= M_PI / 72;

				double rotation = vars->player->rotation;
				double oldDirX = 0;
				double oldDirY = -1;
				vars->player->dirX = oldDirX * cos(rotation) - oldDirY * sin(rotation);
				vars->player->dirY = oldDirX * sin(rotation) + oldDirY * cos(rotation);
				double oldPlaneX = 1;
				double oldPlaneY = 0;
				vars->player->planeX = oldPlaneX * cos(rotation) - oldPlaneY * sin(rotation);
				vars->player->planeY = oldPlaneX * sin(rotation) + oldPlaneY * cos(rotation);
			}
			else if (vars->keys & 0x1) // right
			{
				vars->player->rotation += M_PI / 72;

				double rotation = vars->player->rotation;
				double oldDirX = 0;
				double oldDirY = -1;
				vars->player->dirX = oldDirX * cos(rotation) - oldDirY * sin(rotation);
				vars->player->dirY = oldDirX * sin(rotation) + oldDirY * cos(rotation);
				double oldPlaneX = 1;
				double oldPlaneY = 0;
				vars->player->planeX = oldPlaneX * cos(rotation) - oldPlaneY * sin(rotation);
				vars->player->planeY = oldPlaneX * sin(rotation) + oldPlaneY * cos(rotation);
			}
		}
		// if (!((vars->keys & 0x32) && (vars->keys & 0x16)))
		// {
		// 	if (vars->keys & 0x32) // up
		// 	{
		// 		if(worldMap[(int)(vars->player->posY)][(int)(vars->player->posX + vars->player->dirX / 8)] == '0')
		// 			vars->player->posX += (vars->player->dirX / 8);
		// 		if(worldMap[(int)(vars->player->posY + vars->player->dirY / 8)][(int)(vars->player->posX)] == '0')
		// 			vars->player->posY += (vars->player->dirY / 8);
		// 	}
		// 	else if (vars->keys & 0x16) // down
		// 	{
		// 		if(worldMap[(int)(vars->player->posY)][(int)(vars->player->posX - vars->player->dirX / 8)] == '0')
		// 			vars->player->posX -= (vars->player->dirX / 8);
		// 		if(worldMap[(int)(vars->player->posY - vars->player->dirY / 8)][(int)(vars->player->posX)] == '0')
		// 			vars->player->posY -= (vars->player->dirY / 8);
		// 	}
		// }

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
	player.posX = 8.5;
	player.posY = 8.5;

	//FACING NORTH FOR THE FIRST TIME OF RUN
	player.dirX = 0;
	player.dirY = -1;
	player.planeX = 1;
	// player.planeY = 0.66;
	player.planeY = 0;
	ml_mlx.player = &player;

	// printf("INIT PART\n");

	t_tex texture;
	// printf("T_TEX\n");
	texture.n.img = 0;
	texture.n.img = mlx_xpm_file_to_image(ml_mlx.mlx, "/Users/yim/42/4_c/cub3D/srcs/OIP-1.xpm", &texture.n_width, &texture.n_height);
	texture.n.addr = 0;
	texture.n.addr = mlx_get_data_addr(texture.n.img, &texture.n.bits_per_pixel, &texture.n.line_length, &texture.n.endian);
	// printf("%p %p\n", texture.n.img, texture.n.addr);
	texture.s.img = mlx_xpm_file_to_image(ml_mlx.mlx, "/Users/minsulee/Desktop/cub3d/cub3D/srcs/south.xpm", &texture.s_width, &texture.s_height);
	texture.s.addr = mlx_get_data_addr(texture.s.img, &texture.s.bits_per_pixel, &texture.s.line_length, &texture.s.endian);
	// printf("%p %p\n", texture.s.img, texture.s.addr);
	texture.e.img = mlx_xpm_file_to_image(ml_mlx.mlx, "/Users/minsulee/Desktop/cub3d/cub3D/srcs/east.xpm", &texture.e_width, &texture.e_height);
	texture.e.addr = mlx_get_data_addr(texture.e.img, &texture.e.bits_per_pixel, &texture.e.line_length, &texture.e.endian);
	// printf("%p %p\n", texture.e.img, texture.e.addr);
	texture.w.img = mlx_xpm_file_to_image(ml_mlx.mlx, "/Users/minsulee/Desktop/cub3d/cub3D/srcs/west.xpm", &texture.w_width, &texture.w_height);
	texture.w.addr = mlx_get_data_addr(texture.w.img, &texture.w.bits_per_pixel, &texture.w.line_length, &texture.w.endian);
	// printf("%p %p\n", texture.w.img, texture.w.addr);
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