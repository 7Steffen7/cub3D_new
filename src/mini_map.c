/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:51:43 by sparth            #+#    #+#             */
/*   Updated: 2024/06/11 16:21:12 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	bresenham(t_data *data, t_vector start, t_vector end)
{
	float	x_step;
	float	y_step;
	int		max;
	float	step;
	int		i;

	i = 1;
	x_step = end.x - start.x;
	y_step = end.y - start.y;
	max = fmaxf(fabsf(x_step), fabsf(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(start.x - end.x) || (int)(start.y - end.y))
	{
		step = i++ / max;
		if (start.y >= 8 && start.y <= 184 && start.x >= 776 && start.x <= 1016)
			mlx_put_pixel(data->img, start.x, start.y, 0x00AAFF77);
		start.x += x_step;
		start.y += y_step;
	}
}

void	map_ray(t_data *data, int index, double perp_len)
{
	float		radian;
	float		len;
	t_vector	start;
	t_vector	end;

	radian = (60 + (index * 0.58823529)) * (M_PI / 180);
	len = perp_len / sin(radian);
	end.x = 896 - ((len * 8) * cos(radian));
	end.y = 96 - ((len * 8) * sin(radian));
	start = (t_vector){896, 96};
	bresenham(data, start, end);
}

// pixel height = 8
// pixel width = 8 

//borders SCREEN WIDTH
//1024 - (1024 / 8) = 896
// 1 Block = 8 pixel
// (1024 - 896) / 8 = 16 with padding +-15 blocks on each direction
// min = 776
// max = 1016

//borders SCREEN HEIGHT
// 768 / 8 = 96
// 1 Block = 8 pixel
// 96 / 8 = 12 with padding +- 11 blocks on each direction
//min = 8
// max = 184

void	draw_block2(t_data *data, t_block map, int x, int y)
{
	int				temp_x;
	int				temp_y;
	float			pos_x;
	float			pos_y;

	temp_x = map.start_x + map.j + (8 * x);
	temp_y = map.start_y + map.k + (8 * y);
	pos_x = (map.pivot_x + (temp_x - map.pivot_x) \
		* cos(map.theta)) - (temp_y - map.pivot_y) * sin(map.theta);
	pos_y = map.pivot_y + (temp_x - map.pivot_x) \
		* sin(map.theta) + (temp_y - map.pivot_y) * cos(map.theta);
	if (pos_y >= 8 && pos_y <= 184 && pos_x >= 776 && pos_x <= 1016)
		mlx_put_pixel(data->img, pos_x, pos_y, map.color);
}

void	draw_block(t_data *data, int y, int x, char type)
{
	t_block	map;

	if (type == '1')
		map.color = wall_color_map;
	else
		map.color = door_color_map;
	map.start_x = data->screen_width - (data->screen_width / 8) \
		- (((int)(data->player->position.x * 10) % 10) * 8 / 10);
	map.start_y = data->screen_height / 8 \
		- (((int)(data->player->position.y * 10) % 10) * 8 / 10);
	map.pivot_x = data->screen_width - (data->screen_width / 8);
	map.pivot_y = ((data->screen_height / 8));
	map.k = 0;
	map.theta = atan2(data->player->direction.x * -1, \
	data->player->direction.y * -1);
	while (map.k < 8)
	{
		map.j = 0;
		while (map.j < 8)
		{
			draw_block2(data, map, x, y);
			map.j++;
		}
		map.k++;
	}
}

void	mini_map(t_data *data)
{
	int	start_x;
	int	start_y;
	int	x;
	int	y;

	start_x = (int)data->player->position.x;
	start_y = (int)data->player->position.y;
	y = -MINIMAP_HEIGHT + 1;
	while (y < MINIMAP_HEIGHT)
	{
		x = -MINIMAP_WIDTH + 1;
		while (x < MINIMAP_WIDTH)
		{
			if (start_y + y < data->map_height && start_x + x < data->map_width
				&& start_y + y >= 0 && start_x + x >= 0)
			{
				if (data->map[start_y + y][start_x + x] == '1'
					|| data->map[start_y + y][start_x + x] == 'D')
					draw_block(data, y, x, data->map[start_y + y][start_x + x]);
			}
			x++;
		}
		y++;
	}
	draw_arrow(data);
}
