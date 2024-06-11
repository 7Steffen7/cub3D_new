/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:21:32 by sparth            #+#    #+#             */
/*   Updated: 2024/06/11 16:22:22 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
