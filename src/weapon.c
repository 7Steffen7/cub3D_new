/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:55:38 by aweissha          #+#    #+#             */
/*   Updated: 2024/06/09 16:10:44 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

unsigned int	find_weapon_color(float x, float y, t_data *data)
{
	mlx_texture_t	*gun;
	unsigned int	color;
	int				gun_x;
	int				gun_y;

	if (data->weapon_shot >= 0)
		gun = data->weapon_shot_textures[data->weapon_shot];
	else
		gun = data->weapon_textures[data->weapon];
	gun_x = (int)gun->width * x;
	gun_y = (int)gun->height * y;
	color = gun->pixels[gun->width * 4 * gun_y + gun_x * 4];
	color *= 256;
	color += gun->pixels[gun->width * 4 * gun_y + gun_x * 4 + 1];
	color *= 256;
	color += gun->pixels[gun->width * 4 * gun_y + gun_x * 4 + 2];
	color *= 256;
	color += gun->pixels[gun->width * 4 * gun_y + gun_x * 4 + 3];
	return (color);
}

void	add_weapon(t_data *data)
{
	int				x;
	int				y;
	unsigned int	color;

	if (data->weapon < 0 && data->weapon_shot < 0)
		return ;
	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = SCREEN_WIDTH / 3;
		while (x < (SCREEN_WIDTH / 3) * 2)
		{
			color = find_weapon_color((float)(x - SCREEN_WIDTH / 3)
					/ ((SCREEN_WIDTH / 3) * 2 - SCREEN_WIDTH / 3),
					(float)(y - SCREEN_HEIGHT / 2)
					/ (SCREEN_HEIGHT - SCREEN_HEIGHT / 2), data);
			if (color != 2300413183 && color != 2300282111
				&& color != 2300413183)
				mlx_put_pixel(data->img, x, y, color);
			x++;
		}
		y++;
	}
	data->weapon_shot = -1;
}
