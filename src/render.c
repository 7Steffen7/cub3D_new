/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:07:03 by aweissha          #+#    #+#             */
/*   Updated: 2024/06/11 14:42:26 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	fill_repeating_pixels(int *counter, int color, t_data *data)
{
	float	ratio;
	int	start;

	start = (*counter) - 1;
	ratio = ((float)data->ray->line_height
			/ data->textures[data->ray->side]->height);
	while (((*counter) - start) < ratio && (*counter) < data->ray->line_bottom)
	{
		if (data->ray->index >= 776 && data->ray->index <= 1016
			&& (*counter) >= 8 && (*counter) <= 184)
		{
				mlx_put_pixel(data->img, data->ray->index,
					*counter, color - 64);
		}
		else
			mlx_put_pixel(data->img, data->ray->index, *counter, color);
		(*counter)++;
	}
}

void	line_to_image(t_data *data)
{
	t_ray	*ray;
	int		counter;
	int		color;

	ray = data->ray;
	counter = ray->line_top;
	while (counter < ray->line_bottom)
	{
		color = find_color_from_texture(counter, data);
		if (ray->index >= 776 && ray->index <= 1016
			&& counter >= 8 && counter <= 184)
			mlx_put_pixel(data->img, ray->index, counter, color - 64);
		else
			mlx_put_pixel(data->img, ray->index, counter, color);
		counter++;
		// if (ray->line_height > (int)data->textures[ray->side]->height)
		// 	fill_repeating_pixels(&counter, color, data);
	}
}

void	render_image(t_data *data)
{
	t_ray	*ray;

	ray = data->ray;
	if (ray->perp_length < 1)
		ray->line_height = data->screen_height;
	else
		ray->line_height = data->screen_height / (float)ray->perp_length;
	ray->line_top = data->screen_height / 2 - ray->line_height / 2;
	ray->line_bottom = data->screen_height / 2 + ray->line_height / 2;
	line_to_image(data);
}
