/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:53:58 by aweissha          #+#    #+#             */
/*   Updated: 2024/06/07 21:23:13 by aweissha         ###   ########.fr       */
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
	// printf("ray dir.x: %f\n", ray->dir.x);
	// printf("ray dir.y: %f\n", ray->dir.y);
	// printf("ray map_x: %d\n", ray->map_x);
	// printf("ray map_y: %d\n", ray->map_y);
	if (ray->dir.x < 0 && is_integer(ray->pos.x) == 1
		&& ray->dir.y < 0 && is_integer(ray->pos.y) == 1 && 0 <= ray->map_y - 1
		&& ray->map_y - 1 < data->map_height && 0 <= ray->map_x - 1 && ray->map_x - 1 < data->map_width
		&& data->map[ray->map_y - 1][ray->map_x - 1] != '0')
	{
		ray->wall = data->map[ray->map_y - 1][ray->map_x - 1];
	}
	else if (ray->dir.x < 0 && is_integer(ray->pos.x) == 1 && 0 <= ray->map_y
		&& ray->map_y < data->map_height && 0 <= ray->map_x - 1 && ray->map_x - 1 < data->map_width
		&& data->map[ray->map_y][ray->map_x - 1] != '0')
	{
		ray->wall = data->map[ray->map_y][ray->map_x - 1];
	}
	else if (ray->dir.y < 0 && is_integer(ray->pos.y) == 1 && 0 <= ray->map_y - 1
		&& ray->map_y - 1 < data->map_height && 0 <= ray->map_x && ray->map_x < data->map_width
		&& data->map[ray->map_y - 1][ray->map_x] != '0')
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

void	check_side(t_ray *ray)
{
	// if ray hits vertical line
	if (fabs(ray->pos.x - round(ray->pos.x)) < fabs(ray->pos.y - round(ray->pos.y))
		&& is_integer(ray->pos.x) == 1)
	{
		if (ray->dir.x > 0)
			ray->side = 1;	// east
		else
			ray->side = 3;	// west
	}
	// else if ray hits horizontal line
	else if (fabs(ray->pos.x - round(ray->pos.x)) > fabs(ray->pos.y - round(ray->pos.y))
		&& is_integer(ray->pos.y) == 1)
	{
		if (ray->dir.y > 0)
			ray->side = 2;	// south
		else
			ray->side = 0;	// north
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


void	ray_algorithm(t_data *data)
{
	t_ray	*ray;

	ray = data->ray;
	while ((ray->wall) == '0' || (ray->wall) == 'd')
	{
		// printf("hello from ray algorithm\n");
		elongate_ray(ray);
		check_for_wall(data);
	}
	calc_perp_length(data);
	calc_texture(data);
}

int	ft_pixel(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	find_color_from_texture(int	counter, t_data *data)
{
	int		color;
	mlx_texture_t	*texture;
	int		tex_width;
	float	f;
	float	a;

	if (data->ray->wall == 'D')
		texture = data->door_texture[0];
	else
		texture = data->textures[data->ray->side];
	tex_width = texture->width;
	f = (0.5 - 0.5 * data->ray->perp_length)/ 0.5;
	a = ((counter - data->ray->line_top) / (float)data->ray->line_height);
	if (data->ray->perp_length < 1)
	{
		data->ray->tex_y = texture->height * (a - a * f + 0.5 * f);
		// ray->tex_y = (int)(((counter - ray->line_top) / (float)ray->line_height) * (data->textures[ray->side]->height - (data->textures[ray->side]->height * factor))) + ((0.5 * data->textures[ray->side]->height) * factor);
	}
	else
		data->ray->tex_y = ((counter - data->ray->line_top) / (float)data->ray->line_height) * texture->height;
	// color = texture->pixels[tex_width * 4 * data->ray->tex_y + data->ray->tex_x * 4];
	// color *= 256;
	// color += texture->pixels[tex_width * 4 * data->ray->tex_y + data->ray->tex_x * 4 + 1];
	// color *= 256;
	// color += texture->pixels[tex_width * 4 * data->ray->tex_y + data->ray->tex_x * 4 + 2];
	// color *= 256;
	// color += texture->pixels[tex_width * 4 * data->ray->tex_y + data->ray->tex_x * 4 + 3];
	color = ft_pixel(texture->pixels[tex_width * 4 * data->ray->tex_y + data->ray->tex_x * 4],
		texture->pixels[tex_width * 4 * data->ray->tex_y + data->ray->tex_x * 4 + 1]
		/ (1.0 + data->ray->perp_length * 0.02),
		texture->pixels[tex_width * 4 * data->ray->tex_y + data->ray->tex_x * 4 + 2]
		/ (1.0 + data->ray->perp_length * 0.02),
		texture->pixels[tex_width * 4 * data->ray->tex_y + data->ray->tex_x * 4 + 3]);
	if (data->map_height > data->map_width)
		color -= 256 * (data->ray->perp_length / data->map_height);
	else
		color -= 256 * (data->ray->perp_length / data->map_width);
	return (color);
}

// int	find_color_from_texture(int	counter, t_data *data)
// {
// 	t_ray	*ray;
// 	u_int32_t		color;
// 	u_int32_t		tex_width;
// 	float	f;
// 	float	a;
// 	u_int32_t	*pixels;

// 	ray = data->ray;
// 	pixels = (u_int32_t *)(data->textures[ray->side]->pixels);
// 	tex_width = data->textures[ray->side]->width;
// 	f = (0.5 - 0.5 * ray->perp_length)/ 0.5;
// 	a = ((counter - ray->line_top) / (float)ray->line_height);
// 	if (ray->perp_length < 1)
// 	{
// 		ray->tex_y = data->textures[ray->side]->height * (a - a * f + 0.5 * f);
// 		// ray->tex_y = (int)(((counter - ray->line_top) / (float)ray->line_height) * (data->textures[ray->side]->height - (data->textures[ray->side]->height * factor))) + ((0.5 * data->textures[ray->side]->height) * factor);
// 	}
// 	else
// 		ray->tex_y = ((counter - ray->line_top) / (float)ray->line_height) * data->textures[ray->side]->height;
// 	color = ((pixels[tex_width * ray->tex_y + ray->tex_x] & 0x00FFFFFF) << 8) | ((pixels[tex_width * ray->tex_y + ray->tex_x] & 0xFF000000) >> 24);
// 	// printf("color hex: %x\n", color);
// 	// color *= 256;
// 	// color += data->textures[ray->side]->pixels[tex_width * 4 * ray->tex_y + ray->tex_x * 4 + 1];
// 	// color *= 256;
// 	// color += data->textures[ray->side]->pixels[tex_width * 4 * ray->tex_y + ray->tex_x * 4 + 2];
// 	// color *= 256;
// 	// color += data->textures[ray->side]->pixels[tex_width * 4 * ray->tex_y + ray->tex_x * 4 + 3];
// 	return (color);
// }


void	fill_repeating_pixels(int *counter, int color, t_data *data)
{
	int	ratio;
	int	start;

	start = *counter - 1;
	ratio = (int)(data->ray->line_height / data->textures[data->ray->side]->height);
	while ((*counter - start) < ratio && *counter < data->ray->line_bottom)
	{
		if (data->ray->index >= 776 && data->ray->index <= 1016 && *counter >= 8 && *counter <= 184)
		{
			if(color % 255 > 127)
				mlx_put_pixel(data->img, data->ray->index, *counter, color - 64);
			else
				mlx_put_pixel(data->img, data->ray->index, *counter, color + 64);
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
	// printf("hello from line_to_image\n");
	while (counter < ray->line_bottom)
	{
		// printf("counter: %d\n", counter);
		color = find_color_from_texture(counter, data);
		if (ray->index >= 776 && ray->index <= 1016 && counter >= 8 && counter <= 184)
			mlx_put_pixel(data->img, ray->index, counter, color - 64);
		else
			mlx_put_pixel(data->img, ray->index, counter, color);
		counter++;
		if (ray->line_height > (int)data->textures[ray->side]->height)
			fill_repeating_pixels(&counter, color, data);
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
	// printf("color: %x\n", color);
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
			color = find_weapon_color((float)(x - SCREEN_WIDTH / 3)/((SCREEN_WIDTH / 3) * 2 - SCREEN_WIDTH / 3), (float)(y - SCREEN_HEIGHT / 2)/(SCREEN_HEIGHT - SCREEN_HEIGHT / 2), data);
			if (color != 2300413183 && color !=	2300282111 && color != 2300413183)
				mlx_put_pixel(data->img, x, y, color);
			x++;
		}
		y++;
	}
	data->weapon_shot = -1;
}

void	raycaster(t_data *data)
{
	int	i;
	double	mini_map_rays[103];
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
		if (i % 10 == 0)
			mini_map_rays[i / 10] = data->ray->perp_length;
			// map_ray(data, i);
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
