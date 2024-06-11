/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:07:59 by aweissha          #+#    #+#             */
/*   Updated: 2024/06/11 15:04:01 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_background(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->screen_height / 2)
	{
		x = 0;
		while (x != data->screen_width)
		{
			if (x >= 776 && x <= 1016 && y >= 8 && y <= 184)
				mlx_put_pixel(data->img, x++, y, data->color_ceiling - 64);
			else
				mlx_put_pixel(data->img, x++, y, data->color_ceiling);
		}
		y++;
	}
	while (y != data->screen_height)
	{
		x = 0;
		while (x != data->screen_width)
			mlx_put_pixel(data->img, x++, y, data->color_floor);
		y++;
	}
}

bool	door_check(char **map, t_data *data)
{
	float	y;
	float	x;

	y = data->player->position.y;
	x = data->player->position.x;
	if (map[(int)(y + WALL_DIST)][(int)(x + WALL_DIST)] != 'd'
		&& map[(int)(y + WALL_DIST)][(int)(x - WALL_DIST)] != 'd'
		&& map[(int)(y - WALL_DIST)][(int)(x + WALL_DIST)] != 'd'
		&& map[(int)(y - WALL_DIST)][(int)(x - WALL_DIST)] != 'd')
		return (true);
	return (false);
}

void	open_close_door(t_data *data)
{
	t_vector		door_position;
	int				map_x;
	int				map_y;
	long			time;
	struct timeval	tv;

	door_position.x = data->player->position.x + (data->player->direction.x \
		/ vector_len(data->player->direction));
	door_position.y = data->player->position.y + (data->player->direction.y \
		/ vector_len(data->player->direction));
	map_x = (int)door_position.x;
	map_y = (int)door_position.y;
	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	if ((time - data->time) >= 200)
	{
		if (data->map[map_y][map_x] == 'D')
			data->map[map_y][map_x] = 'd';
		else if (data->map[map_y][map_x] == 'd')
		{
			if (door_check(data->map, data))
				data->map[map_y][map_x] = 'D';
		}
		data->time = time;
	}
}

void	ft_hook(void *param)
{
	t_data	*data;
	int		mouse_x;
	int		mouse_y;

	mouse_x = 0;
	mouse_y = 0;
	data = param;
	player_movement(data, mouse_x, mouse_y);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_1))
		data->weapon = -1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_2))
		data->weapon = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_3))
		data->weapon = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_4))
		data->weapon = 2;
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
		open_close_door(data);
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
		data->weapon_shot = data->weapon;
	print_background(data);
	raycaster(data);
	mini_map(data);
}

	// printf("player_x: %f\n", data->player->position.x);
	// printf("player_y: %f\n", data->player->position.y);
	// printf("dir_x: %f\n", data->player->direction.x);
	// printf("dir_y: %f\n", data->player->direction.y);

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = init_data(argc, argv);
	init_textures(data);
	raycaster(data);
	mlx_set_mouse_pos(data->mlx, data->mouse_temp_x, data->mouse_temp_y);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	free_everything(data);
}
