/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:53:58 by aweissha          #+#    #+#             */
/*   Updated: 2024/05/16 18:46:38 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	get_lower(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

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

int is_integer(double x)
{
	// printf("hello from is_integer\n");
    return (fabs(x - round(x)) < 1e-15);
}

void	check_side(t_data *data)
{
	t_ray	*ray;
	
	ray=data->ray;
	if (is_integer(ray->pos.x == 1)
		&& is_integer(ray->pos.y == 1))
			ray->side = 0;
	else if (is_integer(ray->pos.x == 1))
		ray->side = 1;
	else if (is_integer(ray->pos.y == 1))
		ray->side = 2;
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
	// printf("hello from check for wall 1\n");
	// printf("ray->map: %d\n", data->map[ray->map_x][ray->map_y]);
	// printf("ray->pos.x: %f\n", ray->pos.x);
	// printf("ray->pos.y: %f\n", ray->pos.y);
	// printf("ray->map_x: %d\n", ray->map_x);
	// printf("ray->map_y: %d\n", ray->map_y);
	// printf("ray->dir.x: %f\n", ray->dir.x);
	// printf("ray->dir.y: %f\n", ray->dir.y);
	
	// if (ray->dir.x < 0 && is_integer(ray->pos.x) == 1
	// 	&& ray->dir.y < 0 && is_integer(ray->pos.y) == 1
	// 	&& data->map[ray->map_x - 1][ray->map_y - 1] != 0)
	// {
	// 	ray->wall = data->map[ray->map_x - 1][ray->map_y - 1];
	// }
	// else if (ray->dir.x < 0 && is_integer(ray->pos.x) == 1
	// 	&& data->map[ray->map_x - 1][ray->map_y] != 0)
	// {
	// 	ray->wall = data->map[ray->map_x - 1][ray->map_y];
	// }
	// else if (ray->dir.y < 0 && is_integer(ray->pos.y) == 1
	// 	&& data->map[ray->map_x][ray->map_y - 1] != 0)
	// {
	// 	ray->wall = data->map[ray->map_x][ray->map_y - 1];
	// }
	// else
	// {
	// 	ray->wall = data->map[ray->map_x][ray->map_y];
	// }
	if (ray->dir.x < 0 && is_integer(ray->pos.x) == 1
		&& ray->dir.y < 0 && is_integer(ray->pos.y) == 1
		&& data->map[ray->map_y - 1][ray->map_x - 1] != 0)
	{
		ray->wall = data->map[ray->map_y - 1][ray->map_x - 1];
	}
	else if (ray->dir.x < 0 && is_integer(ray->pos.x) == 1
		&& data->map[ray->map_y][ray->map_x - 1] != 0)
	{
		ray->wall = data->map[ray->map_y][ray->map_x - 1];
	}
	else if (ray->dir.y < 0 && is_integer(ray->pos.y) == 1
		&& data->map[ray->map_y - 1][ray->map_x] != 0)
	{
		ray->wall = data->map[ray->map_y - 1][ray->map_x];
	}
	else
	{
		ray->wall = data->map[ray->map_y][ray->map_x];
	}
}

double	vector_len(t_vector vector)
{
	return (sqrt(pow(vector.x, 2) + pow(vector.y, 2)));
}

void	calc_perp_length(t_data *data)
{
	t_ray		*ray;
	t_player	*player;

	ray = data->ray;
	player = data->player;
	ray->perp_length =
		((sqrt(pow(ray->pos.x - ray->start_pos.x, 2)
		+ pow(ray->pos.y - ray->start_pos.y, 2))
		- sqrt(pow(vector_len(player->direction), 2)
		+ pow((vector_len(player->screen) * ray->factor), 2)))
		/ 
		(sqrt(pow(vector_len(player->direction), 2)
		+ pow((vector_len(player->screen) * ray->factor), 2)))
		* vector_len(player->direction))
		+
		vector_len(player->direction);
}

void	ray_algorithm(t_data *data)
{
	t_ray	*ray;

	ray = data->ray;
	while (!(ray->wall))
	{
		// printf("hello from ray algorithm\n");
		elongate_ray(ray);
		check_for_wall(data);
	}
	calc_perp_length(data);
}

void	line_to_image(t_data *data)
{
	t_ray	*ray;
	int		counter;

	ray = data->ray;
	counter = ray->line_top;
	// printf("hello from line_to_image\n");
	while (counter < ray->line_bottom)
	{
		// printf("counter: %d\n", counter);
		mlx_put_pixel(data->img, ray->index, counter, 0xFF0000FF);
		counter++;
	}
}

/*
This functions looks at the length of the last ray
and converts the information into the image by filling
each pixel-column of the image correctly.
*/
void	render_image(t_data *data)
{
	t_ray	*ray;

	ray = data->ray;
	// printf("hello from render_image\n");
	if (ray->perp_length < 1)
		ray->line_height = data->screen_height;
	else
		ray->line_height = data->screen_height / (float)ray->perp_length;
		// ray->line_height = (float)(data->screen_height / ray->perp_length);
	// printf("perp_length: %f\n", ray->perp_length);
	// printf("screen_height: %d\n", data->screen_height);
	// printf("line_height: %d\n", ray->line_height);
	ray->line_top = data->screen_height / 2 - ray->line_height / 2;
	// printf("line_top: %d\n", ray->line_top);
	ray->line_bottom = data->screen_height / 2 + ray->line_height / 2;
	// printf("line_bottom: %d\n", ray->line_bottom);
	line_to_image(data);
}

void	raycaster(t_data *data)
{
	int	i;
	// t_vector ray_len;
	i = 0;
	while (i < data->screen_width)
	{
		// printf("hello from raycaster\n");
		init_ray(i, data);
		// printf("hello from raycaster\n");
		ray_algorithm(data);
		
		// ray_len.x = data->ray->pos.x - data->ray->start_pos.x;
		// ray_len.y = data->ray->pos.y - data->ray->start_pos.y;
		// printf("ray index: %d, ray_length: %f\n", data->ray->index, vector_len(ray_len));
		// printf("ray_index: %d x: %f y: %f\n", data->ray->index, data->ray->pos.x, data->ray->pos.y);
		
		
		render_image(data);
		i++;
	}
}

