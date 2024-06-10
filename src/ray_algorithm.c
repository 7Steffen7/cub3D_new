/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:01:37 by aweissha          #+#    #+#             */
/*   Updated: 2024/06/09 23:55:21 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	find_factor(t_ray *ray)
{
	double	a_x;
	double	a_y;
	double	a;

	a_x = DBL_MAX;
	a_y = DBL_MAX;
	if (ray->dir.x > 0)
		a_x = (1 - ray->pos.x + ray->map_x) / ray->dir.x;
	else if (ray->dir.x < 0)
		a_x = (-ray->pos.x + ray->map_x) / ray->dir.x;
	if (ray->dir.y > 0)
		a_y = (1 - ray->pos.y + ray->map_y) / ray->dir.y;
	else if (ray->dir.y < 0)
		a_y = (-ray->pos.y + ray->map_y) / ray->dir.y;
	if (a_x == 0)
		a_x = -1 / ray->dir.x;
	if (a_y == 0)
		a_y = -1 / ray->dir.y;
	a = get_lower(a_x, a_y);
	return (a);
}

void	elongate_ray(t_ray *ray)
{
	double	a;

	a = find_factor(ray);
	ray->pos.x = ray->pos.x + ray->dir.x * a;
	ray->pos.y = ray->pos.y + ray->dir.y * a;
	ray->map_x = (int)ray->pos.x;
	ray->map_y = (int)ray->pos.y;
}

/*
This function checks, if the ray is in a wall. 
The ray is also consideres as in a wall,
when its for example at position (2.0/1.5) and square (1/1) is a wall, 
when the ray is facing to negative x. 
When there is a negative dir in the ray,
the previous square has to be checked.
*/
void	check_for_wall(t_data *data)
{
	t_ray	*ray;

	ray = data->ray;
	if (ray->dir.x < 0 && is_integer(ray->pos.x) == 1
		&& ray->dir.y < 0 && is_integer(ray->pos.y) == 1 && 0 <= ray->map_y - 1
		&& ray->map_y - 1 < data->map_height && 0 <= ray->map_x - 1
		&& ray->map_x - 1 < data->map_width
		&& data->map[ray->map_y - 1][ray->map_x - 1] != '0')
		ray->wall = data->map[ray->map_y - 1][ray->map_x - 1];
	else if (ray->dir.x < 0 && is_integer(ray->pos.x) == 1 && 0 <= ray->map_y
		&& ray->map_y < data->map_height && 0 <= ray->map_x - 1
		&& ray->map_x - 1 < data->map_width
		&& data->map[ray->map_y][ray->map_x - 1] != '0')
		ray->wall = data->map[ray->map_y][ray->map_x - 1];
	else if (ray->dir.y < 0 && is_integer(ray->pos.y) == 1
		&& 0 <= ray->map_y - 1
		&& ray->map_y - 1 < data->map_height && 0 <= ray->map_x
		&& ray->map_x < data->map_width
		&& data->map[ray->map_y - 1][ray->map_x] != '0')
		ray->wall = data->map[ray->map_y - 1][ray->map_x];
	else
		ray->wall = data->map[ray->map_y][ray->map_x];
}

void	calc_perp_length(t_data *data)
{
	t_ray		*ray;
	t_player	*player;

	ray = data->ray;
	player = data->player;
	ray->perp_length
		= ((sqrtf(powf(ray->pos.x - ray->start_pos.x, 2)
					+ powf(ray->pos.y - ray->start_pos.y, 2))
				- sqrtf(powf(vector_len(player->direction), 2)
					+ powf((vector_len(player->screen) * ray->factor), 2)))
			/ (sqrtf(powf(vector_len(player->direction), 2)
					+ powf((vector_len(player->screen) * ray->factor), 2)))
			* vector_len(player->direction))
		+ vector_len(player->direction);
}
