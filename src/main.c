/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:07:59 by aweissha          #+#    #+#             */
/*   Updated: 2024/05/28 16:51:36 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// char worldMap[MAP_HEIGHT][MAP_WIDTH]=
// {
// {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
// {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','0','0','0','0','0','1','1','1','1','1','0','0','0','0','1','0','1','0','1','0','0','0','1'},
// {'1','0','0','0','0','0','1','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','0','0','0','0','0','1','0','0','0','1','0','0','0','0','1','0','0','0','1','0','0','0','1'},
// {'1','0','0','0','0','0','1','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','0','0','0','0','0','1','1','0','1','1','0','0','0','0','1','0','1','0','1','0','0','0','1'},
// {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','1','1','1','1','1','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','1','0','1','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','1','0','0','0','0','1','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','1','0','1','0','0','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','1','0','1','1','1','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','1','1','1','1','1','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},
// {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}
// };

// char worldMap[MAP_HEIGHT][MAP_WIDTH]=
// {
// {"111111111111111111111111"},
// {"100000000000000000000001"},
// {"100000000000000000000001"},
// {"100000000000000000000001"},
// {"100000111110000101010001"},
// {"100000100010000000000001"},
// {"100000100010000100010001"},
// {"100000100010000000000001"},
// {"100000110110000101010001"},
// {"100000000000000000000001"},
// {"100000000000000000000001"},
// {"100000000000000000000001"},
// {"100000000000000000000001"},
// {"100000000000000000000001"},
// {"100000000000000000000001"},
// {"100000000000000000000001"},
// {"111111111000000000000001"},
// {"110100001000000000000001"},
// {"110000101000000000000001"},
// {"110100001000000000000001"},
// {"110111111000000000000001"},
// {"110000000000000000000001"},
// {"111111111000000000000001"},
// {"111111111111111111111111"}
// };

// // // for testing, parse_map() just defines data->map as worldMap
// void	parse_map(t_data *data, char *argv[])
// {
// 	int	i;
// 	int	j;

// 	(void)argv;
// 	i = 0;
// 	j = 0;
//     for (int i = 0; i < MAP_HEIGHT; i++) 
// 	{
//         for (int j = 0; j < MAP_WIDTH; j++) 
// 		{
//             data->map[i][j] = worldMap[i][j];
// 			printf("%c", data->map[i][j]);
//         }
// 		printf("\n");
//     }
// }

// void	print_map(t_data *data)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
//     for (int y = 0; y < mapHeight; y++) 
// 	{
//         for (int x = 0; x < mapWidth; x++) 
// 		{
// 			printf("%d,", data->map[x][y]);
//         }
// 		printf("\n");
//     }
// }

void    print_background(t_data *data)
{
	int x;
	int y;
	
	y = 0;
	while (y < data->screen_height / 2)
	{
		x = 0;
		while (x != data->screen_width)
			mlx_put_pixel(data->img, x++, y, data->color_ceiling);
			// mlx_put_pixel(data->img, x++, y, 0x87CEEBFF);
		y++;
	}
	while (y != data->screen_height)
	{
		x = 0;
		while (x != data->screen_width)
			mlx_put_pixel(data->img, x++, y, data->color_floor);
			// mlx_put_pixel(data->img, x++, y, 0x00000000);
		y++;
	}
}

// atan2 = return: angle in radians
// perp = perpendicular vector
void	ft_hook(void *param)
{
	t_data *data = param;
	float	temp_y;
	float	temp_x;
	float	speed;
	float	angle;
	float	perp_x;
	float	perp_y;
	double	radian;
	float	temp_straight_x;
	float	temp_straight_y;
	float	temp_dir_x;
	float	temp_dir_y;

	temp_straight_x = data->player->position.x;
	temp_straight_y = data->player->position.y;
	temp_dir_x = data->player->position.x;
	temp_dir_y = data->player->position.y;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		radian = 2 * (PI / 180);
		temp_x = data->player->direction.x;
		temp_y = data->player->direction.y;
		data->player->direction.x = temp_x * cos(radian) - temp_y * sin(radian);
		data->player->direction.y = temp_x * sin(radian) + temp_y * cos(radian);
		temp_x = data->player->screen.x;
		temp_y = data->player->screen.y;
		data->player->screen.x = temp_x * cos(radian) - temp_y * sin(radian);
		data->player->screen.y = temp_x * sin(radian) + temp_y * cos(radian);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		radian = -2 * (PI / 180);
		temp_x = data->player->direction.x;
		temp_y = data->player->direction.y;
		data->player->direction.x = temp_x * cos(radian) - temp_y * sin(radian);
		data->player->direction.y = temp_x * sin(radian) + temp_y * cos(radian);
		temp_x = data->player->screen.x;
		temp_y = data->player->screen.y;
		data->player->screen.x = temp_x * cos(radian) - temp_y * sin(radian);
		data->player->screen.y = temp_x * sin(radian) + temp_y * cos(radian);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		speed = 0.1;
		angle = atan2(data->player->direction.y, data->player->direction.x);
		temp_straight_x += speed * cos(angle);
		temp_straight_y += speed * sin(angle);
		// if (temp_straight_x > WALL_DIST && temp_straight_x < MAP_WIDTH - WALL_DIST)
		// 	data->player->position.x = temp_straight_x;
		// if  (temp_straight_y > WALL_DIST && temp_straight_y < MAP_HEIGHT - WALL_DIST)
		// 	data->player->position.y = temp_straight_y;
		if (data->map[(int)(data->player->position.y)][(int)(temp_straight_x + WALL_DIST)] != '1'
			&& data->map[(int)(data->player->position.y)][(int)(temp_straight_x - WALL_DIST)] != '1')
			data->player->position.x = temp_straight_x;
		if (data->map[(int)(temp_straight_y + WALL_DIST)][(int)(data->player->position.x)] != '1'
			&& data->map[(int)(temp_straight_y - WALL_DIST)][(int)(data->player->position.x)] != '1')
			data->player->position.y = temp_straight_y;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		speed = -0.1;
		angle = atan2(data->player->direction.y, data->player->direction.x);
		temp_straight_x += speed * cos(angle);
		temp_straight_y += speed * sin(angle);
		if (data->map[(int)(data->player->position.y)][(int)(temp_straight_x + WALL_DIST)] != '1'
			&& data->map[(int)(data->player->position.y)][(int)(temp_straight_x - WALL_DIST)] != '1')
			data->player->position.x = temp_straight_x;
		if (data->map[(int)(temp_straight_y + WALL_DIST)][(int)(data->player->position.x)] != '1'
			&& data->map[(int)(temp_straight_y - WALL_DIST)][(int)(data->player->position.x)] != '1')
			data->player->position.y = temp_straight_y;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		speed = 0.2;
		perp_x = -data->player->direction.y;
		perp_y = data->player->direction.x;
		temp_dir_x += speed * perp_x;
		temp_dir_y += speed * perp_y;
		if (data->map[(int)(data->player->position.y)][(int)(temp_dir_x + WALL_DIST)] != '1'
			&& data->map[(int)(data->player->position.y)][(int)(temp_dir_x - WALL_DIST)] != '1')
			data->player->position.x = temp_dir_x;
		if (data->map[(int)(temp_dir_y + WALL_DIST)][(int)(data->player->position.x)] != '1'
			&& data->map[(int)(temp_dir_y - WALL_DIST)][(int)(data->player->position.x)] != '1')
			data->player->position.y = temp_dir_y;

		// if (temp_dir_x > WALL_DIST && temp_dir_x < MAP_WIDTH - WALL_DIST)
		// 	data->player->position.x = temp_dir_x;
		// if (temp_dir_y > WALL_DIST && temp_dir_y < MAP_HEIGHT - WALL_DIST)
		// 	data->player->position.y = temp_dir_y;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		speed = -0.2;
		perp_x = -data->player->direction.y;
		perp_y = data->player->direction.x;
		temp_dir_x += speed * perp_x;
		temp_dir_y += speed * perp_y;
		if (data->map[(int)(data->player->position.y)][(int)(temp_dir_x + WALL_DIST)] != '1'
			&& data->map[(int)(data->player->position.y)][(int)(temp_dir_x - WALL_DIST)] != '1')
			data->player->position.x = temp_dir_x;
		if (data->map[(int)(temp_dir_y + WALL_DIST)][(int)(data->player->position.x)] != '1'
			&& data->map[(int)(temp_dir_y - WALL_DIST)][(int)(data->player->position.x)] != '1')
			data->player->position.y = temp_dir_y;
	}
	// printf("player_x: %f\n", data->player->position.x);
	// printf("player_y: %f\n", data->player->position.y);
	print_background(data);
	raycaster(data);
	mini_map(data);
}

void	init_textures(t_data *data)
{
	data->textures[0] = mlx_load_png(data->path_to_the_north_texture);
	if (!(data->textures[0]))
		ft_mlx_error_and_free(mlx_strerror(mlx_errno), mlx_errno, data);
	data->textures[1] = mlx_load_png(data->path_to_the_east_texture);
	if (!(data->textures[1]))
		ft_mlx_error_and_free(mlx_strerror(mlx_errno), mlx_errno, data);	
	data->textures[2] = mlx_load_png(data->path_to_the_south_texture);
	if (!(data->textures[2]))
		ft_mlx_error_and_free(mlx_strerror(mlx_errno), mlx_errno, data);
	data->textures[3] = mlx_load_png(data->path_to_the_west_texture);
	if (!(data->textures[3]))
		ft_mlx_error_and_free(mlx_strerror(mlx_errno), mlx_errno, data);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	// (void)argv;
	// printf("hello\n");
	data = init_data(argc, argv);
	// parse_map(data, argv);
	// print_map(data);
	init_textures(data);
	raycaster(data);

	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	free_everything(data);
}
//  to do:
// reset image before raycasting whenever a movement is made