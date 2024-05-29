/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:51:43 by sparth            #+#    #+#             */
/*   Updated: 2024/05/28 22:53:19 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	mini_map(t_data *data)
{
	int x;
	int j;
	int y;
	int k;
	int i;
	int h;
	int	block_height;
	int	block_width;

	block_width = ((data->screen_width / 4) / data->map_width);
	block_height = ((data->screen_height / 4) / data->map_height);
	printf("block_width: %d\n", block_width);
	printf("block_height: %d\n", block_height);
	
	// y = data->screen_height / 4;
	// while (y--)
	// {
	// 	// x = 0;
	// 	x = data->screen_width - data->screen_width / 4;
	// 	while (x != data->screen_width)
	// 		// mlx_put_pixel(data->img, x++, y, data->color_ceiling);
	// 		mlx_put_pixel(data->img, x++, y, 0x87CEEBFF);
	// 	// y++;
	// }
	k = 0;
	h = 0;
	while (k < data->map_height)
	{
		y = 0;
		while (y < block_width)
		{
			i = 0;
			j = 0;
			while (j < data->map_width)
			{
				x = 0;
				while (x < block_width)
				{
					if (k == (int)data->player->position.y && j == (int)data->player->position.x)
						mlx_put_pixel(data->img, i++, h, 0xFF0000FF);
					else if (data->map[k][j] == '1')
						mlx_put_pixel(data->img, i++, h, 0xFFFFEBFF);
					else
						mlx_put_pixel(data->img, i++, h, 0x87CEEBFF);
					x++;
				}
				j++;
			}
			h++;
			y++;
		}
		k++; 
	}
}