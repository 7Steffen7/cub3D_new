/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:51:43 by sparth            #+#    #+#             */
/*   Updated: 2024/05/31 18:33:50 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void	mini_map(t_data *data)
// {
// 	int x;
// 	int j;
// 	int y;
// 	int k;
// 	int i;
// 	int h;
// 	int	block_height;
// 	int	block_width;

// 	block_width = ((data->screen_width / 4) / data->map_width);
// 	block_height = ((data->screen_height / 4) / data->map_height);
// 	printf("block_width: %d\n", block_width);
// 	printf("block_height: %d\n", block_height);
	

// 	k = 0;
// 	h = 0;
// 	while (k < data->map_height)
// 	{
// 		y = 0;
// 		while (y < block_width)
// 		{
// 			i = 0;
// 			j = 0;
// 			while (j < data->map_width)
// 			{
// 				x = 0;
// 				while (x < block_width)
// 				{
// 					if (k == (int)data->player->position.y && j == (int)data->player->position.x)
// 						mlx_put_pixel(data->img, i++, h, 0xFF0000FF);
// 					else if (data->map[k][j] == '1')
// 						mlx_put_pixel(data->img, i++, h, 0xFFFFEBFF);
// 					else
// 						mlx_put_pixel(data->img, i++, h, 0x87CEEBFF);
// 					x++;
// 				}
// 				j++;
// 			}
// 			h++;
// 			y++;
// 		}
// 		k++; 
// 	}
// }


// pixel height = 8
// pixel width = 8 
void	draw_block(t_data *data, int y, int x, unsigned int color)
{
	int	map_start_x;
	int	map_start_y;
	int	j;
	int	k;
	int	y_offset;
	int	x_offset;
	int temp_x;
	int temp_y;

	x_offset = (int)(data->player->position.x * 10) % 10;
	y_offset = (int)(data->player->position.y * 10) % 10;
	x_offset = x_offset * 8 / 10;
	y_offset = y_offset * 8 / 10;
	// printf("x_offset: %d\n", x_offset);
	// printf("y_offset: %d\n", y_offset);
	map_start_x = data->screen_width - (data->screen_width / 8);
	map_start_y = data->screen_height / 8;
	if (color == 0x87CEEBFF)
	{
		map_start_x -= x_offset;
		map_start_y -= y_offset;
	}
	// else
	// {
	// 	map_start_x -= x_offset;
	// 	map_start_y -= y_offset;
	// }
	k = 0;
	while (k < 8)
	{
		j = 0;
		while (j < 8)
		{
			temp_x = map_start_x + j + (8 * x);
			temp_y = map_start_y + k + (8 * y);
			mlx_put_pixel(data->img, temp_x, temp_y, color);
			// mlx_put_pixel(data->img, map_start_x + j + (8 * x), map_start_y + k + (8 * y), color);
			j++;
		}
		k++;
	}
}

// player start position is in the middle of the map 
// the map is getting printed starting from this position

// step 1. typecast the player position as int (just print it is as a non wall square)
// step 2. consider the float value of the player
// step 3. try to implement map rotation
// alternative implement arrow that shows player direction

void	mini_map(t_data *data)
{
	int	start_x;
	int	start_y;
	int	width_max;
	int	height_max;
	int	x;
	int	y;


	// 128 / 8 - 1
	width_max = 15;
	// 192 / 8 - 1
	height_max = 11;
	start_x = (int)data->player->position.x;
	start_y = (int)data->player->position.y;
	// printing left down quarter of the map

	y = -height_max ;
	while (y < height_max + 1)
	{
		x = -width_max ;
		while (x < width_max)
		{
			draw_block(data, y, x, 0xFFFFEBFF);
			x++;
		}	
		y++;
	}

	y = -height_max + 1;
	while (y < height_max)
	{
		x = -width_max + 1;
		while (x < width_max)
		{
			if (start_y + y == start_y && start_x + x == start_x)
				draw_block(data, y, x, 0xFF0000FF);
			else if (start_y + y < data->map_height && start_x + x < data->map_width
				&& start_y + y >= 0 && start_x + x >= 0
				&& data->map[start_y + y][start_x + x] == '1')
				draw_block(data, y, x, 0x87CEEBFF);
			x++;
		}	
		y++;
	}
	
}