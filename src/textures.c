/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:57:13 by aweissha          #+#    #+#             */
/*   Updated: 2024/06/09 16:27:05 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_side(t_ray *ray)
{
	if (fabs(ray->pos.x - round(ray->pos.x))
		< fabs(ray->pos.y - round(ray->pos.y))
		&& is_integer(ray->pos.x) == 1)
	{
		if (ray->dir.x > 0)
			ray->side = 1;
		else
			ray->side = 3;
	}
	else if (fabs(ray->pos.x - round(ray->pos.x))
		> fabs(ray->pos.y - round(ray->pos.y))
		&& is_integer(ray->pos.y) == 1)
	{
		if (ray->dir.y > 0)
			ray->side = 2;
		else
			ray->side = 0;
	}
}

void	calc_texture(t_data *data)
{
	t_ray	*ray;

	ray = data->ray;
	check_side(ray);
	if (ray->side == 0 || ray->side == 2)
		ray->wall_x = ray->pos.x;
	else if (ray->side == 1 || ray->side == 3)
		ray->wall_x = ray->pos.y;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->wall == 'D')
		ray->tex_x = (int)(ray->wall_x * data->door_texture[0]->width);
	else
		ray->tex_x = (int)(ray->wall_x * data->textures[ray->side]->width);
}

void	calc_tex_y(int counter, mlx_texture_t *texture, t_data *data)
{
	float	f;
	float	a;

	f = (0.5 - 0.5 * data->ray->perp_length) / 0.5;
	a = ((counter - data->ray->line_top) / (float)data->ray->line_height);
	if (data->ray->perp_length < 1)
		data->ray->tex_y = texture->height * (a - a * f + 0.5 * f);
	else
	{
		data->ray->tex_y = ((counter - data->ray->line_top)
				/ (float)data->ray->line_height) * texture->height;
	}
}

int	find_color_from_texture(int counter, t_data *data)
{
	int				color;
	mlx_texture_t	*texture;
	int				tex_width;

	if (data->ray->wall == 'D')
		texture = data->door_texture[0];
	else
		texture = data->textures[data->ray->side];
	tex_width = texture->width;
	calc_tex_y(counter, texture, data);
	color = ft_pixel(texture->pixels[tex_width * 4 * data->ray->tex_y
			+ data->ray->tex_x * 4],
			texture->pixels[tex_width * 4 * data->ray->tex_y
			+ data->ray->tex_x * 4 + 1]
			/ (1.0 + data->ray->perp_length * 0.02),
			texture->pixels[tex_width * 4 * data->ray->tex_y
			+ data->ray->tex_x * 4 + 2]
			/ (1.0 + data->ray->perp_length * 0.02),
			texture->pixels[tex_width * 4 * data->ray->tex_y
			+ data->ray->tex_x * 4 + 3]);
	if (data->map_height > data->map_width)
		color -= 256 * (data->ray->perp_length / data->map_height);
	else
		color -= 256 * (data->ray->perp_length / data->map_width);
	return (color);
}
