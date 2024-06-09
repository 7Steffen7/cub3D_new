/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:53:58 by aweissha          #+#    #+#             */
/*   Updated: 2024/06/09 16:33:40 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ray_algorithm(t_data *data)
{
	t_ray	*ray;

	ray = data->ray;
	while ((ray->wall) == '0' || (ray->wall) == 'd')
	{
		elongate_ray(ray);
		check_for_wall(data);
	}
	calc_perp_length(data);
	calc_texture(data);
}

void	raycaster(t_data *data)
{
	int		i;
	double	mini_map_rays[103];

	i = 0;
	while (i < data->screen_width)
	{
		init_ray(i, data);
		ray_algorithm(data);
		render_image(data);
		if (i % 10 == 0)
			mini_map_rays[i / 10] = data->ray->perp_length;
		i++;
	}
	i = 0;
	while (i < 102)
	{
		map_ray(data, i, mini_map_rays[i]);
		i++;
	}
	add_weapon(data);
}
