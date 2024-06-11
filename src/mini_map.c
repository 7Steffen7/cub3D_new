/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:51:43 by sparth            #+#    #+#             */
/*   Updated: 2024/06/11 15:20:22 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    bresenham(t_data *data, float x0, float x1, float y0, float y1)
{
    float    x_step;
    float    y_step;
    int        max;
    float    step;
    int        i;

    i = 1;
    x_step = x1 - x0;
    y_step = y1 - y0;
    max = fmaxf(fabsf(x_step),fabsf(y_step));
    x_step /= max;
    y_step /= max;

    while((int)(x0 - x1) || (int)(y0 - y1))
    {
        step = i++ / max;
        if (y0 >= 8 && y0 <= 184 && x0 >= 776 && x0 <= 1016)
            mlx_put_pixel(data->img, x0, y0, 0x00AAFF77);
            // mlx_put_pixel(data->img, x0, y0, 0xFFFF00FF);
        x0 += x_step;
        y0 += y_step;
    }
}

void	map_ray(t_data *data, int index, double perp_len)
{
	float	radian;
	int		x;
	int		y;
	float	len;
	

	radian = (60 + (index * 0.58823529)) * (M_PI / 180);
	len = perp_len / sin(radian);
	x = 896 - ((len * 8) * cos(radian));
	y = 96 - ((len * 8) * sin(radian));
	bresenham(data, 896, x, 96, y);
}

void	draw_arrow(t_data *data)
{
	int	player_x;
	int	player_y;
	int	i;
	int	step;
	
	player_x = 896;
	player_y = 96;
	
	player_y -= 6;
	i = 0;
	step = 0;
	while (i > -6)
	{
		while (i <= step)
			mlx_put_pixel(data->img, player_x + i++, player_y, 0xFFFFFF55);
		i -= 1;
		i *= -1;
		player_y++;
		while (i <= step)
			mlx_put_pixel(data->img, player_x + i++, player_y, 0xFFFFFF55);
		player_y++;
		i *= -1;
		step++;
	}
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

void	draw_block(t_data *data, int y, int x, char type)
{
	int				map_start_x;
	int				map_start_y;
	int				j;
	int				k;
	int 			temp_x;
	int 			temp_y;
	float			theta;
	int				pivot_x;
	int				pivot_y;
	float			pos_x;
	float			pos_y;
	unsigned int	color;

	if (type == '1')
		color = WALL_COLOR_MAP;
	else
		color = DOOR_COLOR_MAP;
	map_start_x = data->screen_width - (data->screen_width / 8) - (((int)(data->player->position.x * 10) % 10) * 8 / 10);
	map_start_y = data->screen_height / 8 - (((int)(data->player->position.y * 10) % 10) * 8 / 10);
	pivot_x = data->screen_width - (data->screen_width / 8 );
	pivot_y = ((data->screen_height / 8));
	k = 0;
	theta = atan2(data->player->direction.x * -1, data->player->direction.y * - 1);
	while (k < 8)
	{
		j = 0;
		while (j < 8)
		{
			temp_x = map_start_x + j + (8 * x);
			temp_y = map_start_y + k + (8 * y);
			pos_x = (pivot_x + (temp_x - pivot_x) * cos(theta)) - (temp_y - pivot_y) * sin(theta);
			pos_y = pivot_y + (temp_x - pivot_x) * sin(theta) + (temp_y - pivot_y) * cos(theta);
			if (pos_y >= 8 && pos_y <= 184 && pos_x >= 776 && pos_x <= 1016)
				mlx_put_pixel(data->img, pos_x, pos_y, color);
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
// 128 / 8 - 1
// 96 / 8 - 1
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
