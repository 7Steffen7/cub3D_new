/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:07:59 by aweissha          #+#    #+#             */
/*   Updated: 2024/06/05 16:32:37 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    print_background(t_data *data)
{
	int x;
	int y;
	
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

void	player_rotation(t_data *data, int speed)
{
	double	radian;
	float	temp_y;
	float	temp_x;

	radian = speed * (PI / 180);
	temp_x = data->player->direction.x;
	temp_y = data->player->direction.y;
	data->player->direction.x = temp_x * cos(radian) - temp_y * sin(radian);
	data->player->direction.y = temp_x * sin(radian) + temp_y * cos(radian);
	temp_x = data->player->screen.x;
	temp_y = data->player->screen.y;
	data->player->screen.x = temp_x * cos(radian) - temp_y * sin(radian);
	data->player->screen.y = temp_x * sin(radian) + temp_y * cos(radian);
}

void	player_vertical_movement(t_data *data, float speed)
{
	float	temp_x;
	float	temp_y;
	float	angle;

	temp_x = data->player->position.x;
	temp_y = data->player->position.y;
	angle = atan2(data->player->direction.y, data->player->direction.x);
	temp_x += speed * cos(angle);
	temp_y += speed * sin(angle);
	if (data->map[(int)(data->player->position.y + WALL_DIST)][(int)(temp_x + WALL_DIST)] != '1'
		&& data->map[(int)(data->player->position.y + WALL_DIST)][(int)(temp_x - WALL_DIST)] != '1'
		&& data->map[(int)(data->player->position.y - WALL_DIST)][(int)(temp_x + WALL_DIST)] != '1'
		&& data->map[(int)(data->player->position.y  - WALL_DIST)][(int)(temp_x - WALL_DIST)] != '1')
		data->player->position.x = temp_x;
	if (data->map[(int)(temp_y + WALL_DIST)][(int)(data->player->position.x + WALL_DIST)] != '1'
		&& data->map[(int)(temp_y - WALL_DIST)][(int)(data->player->position.x + WALL_DIST)] != '1' 
		&& data->map[(int)(temp_y + WALL_DIST)][(int)(data->player->position.x - WALL_DIST)] != '1'
		&& data->map[(int)(temp_y - WALL_DIST)][(int)(data->player->position.x - WALL_DIST )] != '1')
		data->player->position.y = temp_y;
}

void	player_horizontal_movement(t_data *data, float speed)
{
	float	perp_x;
	float	perp_y;
	float	temp_x;
	float	temp_y;

	perp_x = -data->player->direction.y;
	perp_y = data->player->direction.x;
	temp_x = data->player->position.x + speed * perp_x;
	temp_y = data->player->position.y + speed * perp_y;
	if (data->map[(int)(data->player->position.y + WALL_DIST)][(int)(temp_x + WALL_DIST)] != '1'
		&& data->map[(int)(data->player->position.y + WALL_DIST)][(int)(temp_x - WALL_DIST)] != '1'
		&& data->map[(int)(data->player->position.y - WALL_DIST)][(int)(temp_x + WALL_DIST)] != '1'
		&& data->map[(int)(data->player->position.y - WALL_DIST)][(int)(temp_x - WALL_DIST)] != '1')
		data->player->position.x = temp_x;
	if (data->map[(int)(temp_y + WALL_DIST)][(int)(data->player->position.x + WALL_DIST)] != '1'
		&& data->map[(int)(temp_y - WALL_DIST)][(int)(data->player->position.x + WALL_DIST)] != '1'
		&& data->map[(int)(temp_y + WALL_DIST)][(int)(data->player->position.x - WALL_DIST)] != '1'
		&& data->map[(int)(temp_y - WALL_DIST)][(int)(data->player->position.x - WALL_DIST)] != '1')
		data->player->position.y = temp_y;
}

// atan2 = return: angle in radians
// perp = perpendicular vector
void	ft_hook(void *param)
{
	t_data *data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		player_rotation(data, 2);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		player_rotation(data, -2);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		player_vertical_movement(data, 0.1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		player_vertical_movement(data, -0.1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		player_horizontal_movement(data, 0.2);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		player_horizontal_movement(data, -0.2);
	if (mlx_is_key_down(data->mlx, MLX_KEY_1))
		data->weapon = -1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_2))
		data->weapon = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_3))
		data->weapon = 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_4))
		data->weapon = 2;
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
		data->weapon_shot = data->weapon;
	
	// printf("player_x: %f\n", data->player->position.x);
	// printf("player_y: %f\n", data->player->position.y);
	// printf("dir_x: %f\n", data->player->direction.x);
	// printf("dir_y: %f\n", data->player->direction.y);
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
	data->weapon_textures[0] = mlx_load_png("./textures/gun.png");
	if (!(data->weapon_textures[0]))
		ft_mlx_error_and_free(mlx_strerror(mlx_errno), mlx_errno, data);
	data->weapon_textures[1] = mlx_load_png("./textures/gun_2.png");
	if (!(data->weapon_textures[1]))
		ft_mlx_error_and_free(mlx_strerror(mlx_errno), mlx_errno, data);
	data->weapon_textures[2] = mlx_load_png("./textures/knive.png");
	if (!(data->weapon_textures[2]))
		ft_mlx_error_and_free(mlx_strerror(mlx_errno), mlx_errno, data);
	data->weapon_shot_textures[0] = mlx_load_png("./textures/gun_shot.png");
	if (!(data->weapon_shot_textures[0]))
		ft_mlx_error_and_free(mlx_strerror(mlx_errno), mlx_errno, data);
	data->weapon_shot_textures[1] = mlx_load_png("./textures/gun_2_shot.png");
	if (!(data->weapon_shot_textures[1]))
		ft_mlx_error_and_free(mlx_strerror(mlx_errno), mlx_errno, data);
	data->weapon_shot_textures[2] = mlx_load_png("./textures/knive_stab.png");
	if (!(data->weapon_shot_textures[2]))
		ft_mlx_error_and_free(mlx_strerror(mlx_errno), mlx_errno, data);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	data = init_data(argc, argv);
	init_textures(data);
	raycaster(data);

	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	free_everything(data);
}
//  to do:
// reset image before raycasting whenever a movement is made