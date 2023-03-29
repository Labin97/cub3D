/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yim <yim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:33:01 by minsulee          #+#    #+#             */
/*   Updated: 2023/03/29 19:28:35y yim              ###   ########.fr       */
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

// void	ml_mlx_draw_line(t_data *data, int x, int draw_start, int draw_end, int color)
// {
// 	int index;

// 	index = draw_start;
// 	while (index <= draw_end)
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
	int	y;
	int	x;

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
	int	y;
	int	x;

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
	double	pos_x;
	double	pos_y;

	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		hit;
	int		side;
	int		map_x;
	int		map_y;

	double	side_dist_x;
	double	side_dist_y;

	int		step_x;
	int		step_y;

	double	perp_wall_dist;

	double	wall_x;

	int		line_height;
	int		draw_start;
	int		draw_end;
	double	tex_width;
	double	tex_height;
	int		*texture;
}	t_projection;











void	projection_init(t_projection *projection, int x, t_player *player)
{
	projection->camera_x = 2 * (x - 1) / (double)SCREEN_WIDTH - 1;
	projection->raydir_x = player->dir_x + player->plane_x * projection->camera_x;
	projection->raydir_y = player->dir_y + player->plane_y * projection->camera_x;
	projection->hit = 0;
	projection->side = 0;
	if (projection->raydir_x == 0)
		projection->delta_dist_x = __DBL_MAX__;
	else
		projection->delta_dist_x = fabs(1 / projection->raydir_x);
	
	if (projection->raydir_y == 0)
		projection->delta_dist_y = __DBL_MAX__;
	else
		projection->delta_dist_y = fabs(1 / projection->raydir_y);
	projection->pos_x = player->pos_x;
	projection->pos_y = player->pos_y;
	projection->map_x = (int) player->pos_x;
	projection->map_y = (int) player->pos_y;
}

void	projection_direction_set(t_projection *projection)
{
		if (projection->raydir_x < 0)
		{
			projection->step_x = -1;
			projection->side_dist_x = (projection->pos_x - projection->map_x) * projection->delta_dist_x;
		}
		else
		{
			projection->step_x = 1;
			projection->side_dist_x = (projection->map_x + 1.0 - projection->pos_x) * projection->delta_dist_x;
		}
		if (projection->raydir_y < 0)
		{
			projection->step_y = -1;
			projection->side_dist_y = (projection->pos_y - projection->map_y) * projection->delta_dist_y;
		}
		else
		{
			projection->step_y = 1;
			projection->side_dist_y = (projection->map_y + 1.0 - projection->pos_y) * projection->delta_dist_y;
		}
}

void	projection_shoot(t_map *map, t_projection *projection)
{
		int hit;

		while (projection->hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (projection->side_dist_x < projection->side_dist_y)
			{
				projection->side_dist_x += projection->delta_dist_x;
				projection->map_x += projection->step_x;
				projection->side = 0;
			}
			else
			{
				projection->side_dist_y += projection->delta_dist_y;
				projection->map_y += projection->step_y;
				projection->side = 1;
			}
			//Check if ray has hit a wall
			if (map->map[projection->map_y][projection->map_x] == '1') // FIX IT TO map_y map_x. IMPORTANT!!!!!!!!!!!!!!!!!!!!!!!!!
				projection->hit = 1;
		}
		// double perp_wall_dist;
		if (projection->side == 0)
			projection->perp_wall_dist = (projection->side_dist_x - projection->delta_dist_x);
		else
			projection->perp_wall_dist = (projection->side_dist_y - projection->delta_dist_y);


//이거 원래 height 다음에 있는건데 겹치는 거 없는 것 같아서 일단 위로 데리고 왔음!
		if (projection->side == 0)
			projection->wall_x = projection->pos_y + projection->perp_wall_dist * projection->raydir_y;
		else
			projection->wall_x = projection->pos_x + projection->perp_wall_dist * projection->raydir_x;
		// if (x == SCREEN_WIDTH / 2)
		// 	printf("side : %d, previous Wall_x : %f, ", projection->side, projection->wall_x);
		projection->wall_x -= floor(projection->wall_x);
}

void	projection_height(t_projection *projection)
{
		projection->line_height = (int)(SCREEN_HEIGHT / projection->perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		projection->draw_start = -(projection->line_height) / 2 + SCREEN_HEIGHT / 2;
		if (projection->draw_start < 0)
			projection->draw_start = 0;
		projection->draw_end = (projection->line_height) / 2 + SCREEN_HEIGHT / 2;
		if (projection->draw_end >= SCREEN_HEIGHT)
			projection->draw_end = SCREEN_HEIGHT - 1;
}

void	projection_side(t_projection *projection)
{

	if (projection->side == 1) // west east
	{
		if (projection->step_y < 0) //west
			projection->side = 0;
		else //east
			projection->side = 1;
	}
	else // north south, side == 0
	{
		if (projection->step_x < 0) //north
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
		projection->tex_width = tex->n_width;
		projection->tex_height = tex->n_height;
	}
	else if (projection->side == 1)
	{
		projection->texture = (int *)tex->s.addr;
		projection->tex_width = tex->s_width;
		projection->tex_height = tex->s_height;
	}
	if (projection->side == 2)
	{
		projection->texture = (int *)tex->w.addr;
		projection->tex_width = tex->w_width;
		projection->tex_height = tex->w_height;
	}
	else if (projection->side == 3)
	{
		projection->texture = (int *)tex->e.addr;
		projection->tex_width = tex->e_width;
		projection->tex_height = tex->e_height;
	}
}

void	projection_draw(t_vars *ml_mlx, t_projection *projection, int x)
{
	int	tex_x;
	int	tex_y;

	tex_x = (int)(projection->wall_x * projection->tex_width);
	if (x == SCREEN_WIDTH / 2)
	{
		printf("pos_x : %f, pos_y : %f, raydir_x : %f, raydir_y : %f, perp_wall_dist : %f, Wall_x : %f, TEX_wIDTH : %f, tex_x : %d\n", projection->pos_x, projection->pos_y, projection->raydir_x, projection->raydir_y, projection->perp_wall_dist, projection->wall_x, projection->tex_width, tex_x);
		printf("\n");
	}
	int	color;
	double step;
	double texPos;


	if (projection->side == 3 || projection->side == 0)
		tex_x = projection->tex_width - tex_x - 1;
	step = 1.0 * projection->tex_height / projection->line_height;
	texPos = (projection->draw_start - (SCREEN_HEIGHT / 2) + projection->line_height / 2) * step;
	for (int y = projection->draw_start; y < projection->draw_end; y++)
	{
		tex_y = (int)(texPos) & (int)(projection->tex_height - 1);
		texPos += step;
		color = projection->texture[(int) projection->tex_width * tex_y + tex_x];
		// ml_mlx_put_pixel(&ml_mlx->data, x, y, projection->texture[(int)projection->tex_width * tex_y + tex_x]);
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

	double pos_x = player->pos_x;
	// pos_x = 22; // test
	double pos_y = player->pos_y;
	// pos_y = 12; // test

	int x = 0, y = 0;
	while (x < SCREEN_WIDTH)
	{
		projection_init(&projection, x, player);
		projection_direction_set(&projection);
		projection_shoot(ml_mlx->map, &projection);
		projection_height(&projection);
		projection_side(&projection);
		projection_texture(ml_mlx->tex, &projection);
		projection_draw(ml_mlx, &projection, x);
		x++;
	}













	mlx_put_image_to_window(ml_mlx->mlx, ml_mlx->win, ml_mlx->data.img, 0, 0);
	return (0);
}


void	find_player_pos(t_vars *ml_mlx)
{
	int		i;
	int		j;

	i = -1;
	while (++i < ml_mlx->map->height)
	{
		j = -1;
		while (++j < ml_mlx->map->width)
		{
			if (ml_mlx->map->map[i][j] == 'N' || ml_mlx->map->map[i][j] == 'S' \
			|| ml_mlx->map->map[i][j] == 'W' || ml_mlx->map->map[i][j] == 'E')
			{
				ml_mlx->player->pos_x = j + 0.5;
				ml_mlx->player->pos_y = i + 0.5;
				if (ml_mlx->map->map[i][j] == 'N')
					ml_mlx->player->dir_y = -1;
				else if (ml_mlx->map->map[i][j] == 'S')
					ml_mlx->player->dir_y = 1;
				else if (ml_mlx->map->map[i][j] == 'W')
					ml_mlx->player->dir_x = -1;
				else if (ml_mlx->map->map[i][j] == 'E')
					ml_mlx->player->dir_x = 1;
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
	else if (key == 123 && !(vars->keys & 32)) // left arrow key
		vars->keys += 32;
	else if (key == 124 && !(vars->keys & 16)) // right arrow key
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
	if (key == 123 && (vars->keys & 32)) // left arrow key
		vars->keys -= 32;
	else if (key == 124 && (vars->keys & 16)) // right arrow key
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
				if(worldMap[(int)(vars->player->pos_y)][(int)(vars->player->pos_x + vars->player->dir_x / 8)] != '1')
					vars->player->pos_x += (vars->player->dir_x / 8);
				if(worldMap[(int)(vars->player->pos_y + vars->player->dir_y / 8)][(int)(vars->player->pos_x)] != '1')
					vars->player->pos_y += (vars->player->dir_y / 8);
			}
			else if (vars->keys & 0x2) // down
			{
				if(worldMap[(int)(vars->player->pos_y)][(int)(vars->player->pos_x - vars->player->dir_x / 8)] != '1')
					vars->player->pos_x -= (vars->player->dir_x / 8);
				if(worldMap[(int)(vars->player->pos_y - vars->player->dir_y / 8)][(int)(vars->player->pos_x)] != '1')
					vars->player->pos_y -= (vars->player->dir_y / 8);
			}
		}
		if (!((vars->keys & 0x4) && (vars->keys & 0x1)))
		if (!((vars->keys & 0x4) && (vars->keys & 0x1)))
		{
			if (vars->keys & 0x4) // left
			{
				vars->player->rotation -= M_PI / 72;

				double rotation = vars->player->rotation;
				double olddir_x = 0;
				double olddir_y = -1;
				vars->player->dir_x = olddir_x * cos(rotation) - olddir_y * sin(rotation);
				vars->player->dir_y = olddir_x * sin(rotation) + olddir_y * cos(rotation);
				double oldplane_x = 1;
				double oldplane_y = 0;
				vars->player->plane_x = oldplane_x * cos(rotation) - oldplane_y * sin(rotation);
				vars->player->plane_y = oldplane_x * sin(rotation) + oldplane_y * cos(rotation);
			}
			else if (vars->keys & 0x1) // right
			{
				vars->player->rotation += M_PI / 72;

				double rotation = vars->player->rotation;
				double olddir_x = 0;
				double olddir_y = -1;
				vars->player->dir_x = olddir_x * cos(rotation) - olddir_y * sin(rotation);
				vars->player->dir_y = olddir_x * sin(rotation) + olddir_y * cos(rotation);
				double oldplane_x = 1;
				double oldplane_y = 0;
				vars->player->plane_x = oldplane_x * cos(rotation) - oldplane_y * sin(rotation);
				vars->player->plane_y = oldplane_x * sin(rotation) + oldplane_y * cos(rotation);
			}
		}
		// if (!((vars->keys & 32) && (vars->keys & 16)))
		// {
		// 	if (vars->keys & 16) // up
		// 	{
		// 		if(worldMap[(int)(vars->player->pos_y)][(int)(vars->player->pos_x + vars->player->plane_x / 8)] == '0')
		// 			vars->player->pos_x += (vars->player->plane_x / 8);
		// 		if(worldMap[(int)(vars->player->pos_y + vars->player->plane_y / 8)][(int)(vars->player->pos_x)] == '0')
		// 			vars->player->pos_y += (vars->player->plane_y / 8);
		// 	}
		// 	else if (vars->keys & 32) // down
		// 	{
		// 		if(worldMap[(int)(vars->player->pos_y)][(int)(vars->player->pos_x - vars->player->plane_x / 8)] == '0')
		// 			vars->player->pos_x -= (vars->player->plane_x / 8);
		// 		if(worldMap[(int)(vars->player->pos_y - vars->player->plane_y / 8)][(int)(vars->player->pos_x)] == '0')
		// 			vars->player->pos_y -= (vars->player->plane_y / 8);
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
	player.pos_x = 8.5;
	player.pos_y = 8.5;

	//FACING NORTH FOR THE FIRST TIME OF RUN
	player.dir_x = 0;
	player.dir_y = -1;
	player.plane_x = 1;
	// player.plane_y = 0.66;
	player.plane_y = 0;
	ml_mlx.player = &player;

	find_player_pos(&ml_mlx);

	// printf("INIT PART\n");

	t_tex texture;
	// printf("T_TEX\n");
	texture.n.img = 0;
	texture.n.img = mlx_xpm_file_to_image(ml_mlx.mlx, ml_mlx.map->no_path, &texture.n_width, &texture.n_height);
	texture.n.addr = 0;
	texture.n.addr = mlx_get_data_addr(texture.n.img, &texture.n.bits_per_pixel, &texture.n.line_length, &texture.n.endian);
	// printf("%p %p\n", texture.n.img, texture.n.addr);
	texture.s.img = mlx_xpm_file_to_image(ml_mlx.mlx, ml_mlx.map->so_path, &texture.s_width, &texture.s_height);
	texture.s.addr = mlx_get_data_addr(texture.s.img, &texture.s.bits_per_pixel, &texture.s.line_length, &texture.s.endian);
	// printf("%p %p\n", texture.s.img, texture.s.addr);
	texture.e.img = mlx_xpm_file_to_image(ml_mlx.mlx, ml_mlx.map->ea_path, &texture.e_width, &texture.e_height);
	texture.e.addr = mlx_get_data_addr(texture.e.img, &texture.e.bits_per_pixel, &texture.e.line_length, &texture.e.endian);
	// printf("%p %p\n", texture.e.img, texture.e.addr);
	texture.w.img = mlx_xpm_file_to_image(ml_mlx.mlx, ml_mlx.map->we_path, &texture.w_width, &texture.w_height);
	texture.w.addr = mlx_get_data_addr(texture.w.img, &texture.w.bits_per_pixel, &texture.w.line_length, &texture.w.endian);
	// printf("%p %p\n", texture.w.img, texture.w.addr);
	ml_mlx.tex = &texture;


	printf("NOT INIT PART\n");
	// printf("rotation : %f\n", player.rotation);
	// printf("pos_x pos_y : %f :: %f \n", player.pos_x, player.pos_y);
	// printf("dir_x dir_y : %f :: %f \n", player.dir_x, player.dir_y);
	// printf("plane_x plane_y : %f :: %f \n", player.plane_x, player.plane_y);
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