/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:26:14 by sparth            #+#    #+#             */
/*   Updated: 2024/06/11 14:30:13 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	able_2_walk(char **map, double y, double x)
{
	if (map[(int)(y + WALL_DIST)][(int)(x + WALL_DIST)] != '1'
		&& map[(int)(y + WALL_DIST)][(int)(x + WALL_DIST)] != 'D'
		&& map[(int)(y + WALL_DIST)][(int)(x - WALL_DIST)] != '1'
		&& map[(int)(y + WALL_DIST)][(int)(x - WALL_DIST)] != 'D'
		&& map[(int)(y - WALL_DIST)][(int)(x + WALL_DIST)] != '1'
		&& map[(int)(y - WALL_DIST)][(int)(x + WALL_DIST)] != 'D'
		&& map[(int)(y - WALL_DIST)][(int)(x - WALL_DIST)] != '1'
		&& map[(int)(y - WALL_DIST)][(int)(x - WALL_DIST)] != 'D')
		return (true);
	return (false);
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
	if (able_2_walk(data->map, data->player->position.y, temp_x))
		data->player->position.x = temp_x;
	if (able_2_walk(data->map, temp_y, data->player->position.x))
		data->player->position.y = temp_y;
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
	if (able_2_walk(data->map, data->player->position.y, temp_x))
		data->player->position.x = temp_x;
	if (able_2_walk(data->map, temp_y, data->player->position.x))
		data->player->position.y = temp_y;
}

void	player_movement(t_data *data, int mouse_x, int mouse_y)
{
	mlx_get_mouse_pos(data->mlx, &mouse_x, &mouse_y);
	if (mouse_x != data->mouse_temp_x && data->mouse == true)
	{
		player_rotation(data, (mouse_x - data->mouse_temp_x) / 2);
		mlx_set_mouse_pos(data->mlx, data->mouse_temp_x, data->mouse_temp_y);
		mouse_x = data->mouse_temp_x;
	}
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
		data->mouse = true;
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_RIGHT))
		data->mouse = false;
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
}
