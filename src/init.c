/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:07:03 by aweissha          #+#    #+#             */
/*   Updated: 2024/05/27 16:33:53 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_ray(int ray_index, t_data *data)
{
	t_player	*player;
	t_ray		*ray;

	if (data->ray == NULL)
		data->ray = malloc(sizeof(t_ray));
	if (data->ray == NULL)
		ft_error_and_free("Memory allocation of ray failed\n", errno, data);	
	player = data->player;
	ray = data->ray;
	ray->index = ray_index;
	ray->start_pos.x = player->position.x;
	ray->start_pos.y = player->position.y;
	ray->pos.x = player->position.x;
	ray->pos.y = player->position.y;
	ray->factor = ((2 * ray_index) / (float)data->screen_width) - 1;
	// printf("ray_factor %f\n", ray->factor);
	ray->dir.x = player->direction.x + player->screen.x * ray->factor;
	ray->dir.y = player->direction.y + player->screen.y * ray->factor;
	ray->map_x = (int)player->position.x;
	ray->map_y = (int)player->position.y;
	ray->wall = '0';
	ray->perp_length = 0;
	ray->side = 0;
	ray->wall_x = 0;
	ray->tex_x = 0;
	ray->tex_y = 0;
	ray->line_height = 0;
	ray->line_bottom = 0;
	ray->line_top = 0;
}

void	ft_init_mlx(t_data *data)
{
	data->mlx = mlx_init(data->screen_width, data->screen_height, "Cub3d", false);
	if (data->mlx == NULL)
		ft_mlx_error_and_free(mlx_strerror(mlx_errno), mlx_errno, data);
	data->img = mlx_new_image(data->mlx, data->screen_width, data->screen_height);
	if (data->img == NULL)
		ft_mlx_error_and_free(mlx_strerror(mlx_errno), mlx_errno, data);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0)
		ft_mlx_error_and_free(mlx_strerror(mlx_errno), mlx_errno, data);
	
}

void	init_player(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	if (data->player == NULL)
		ft_error("Memory allocation of player struct failed\n", errno);
	find_player(data);
	if (data->init_player_dir == 'N')
	{
		data->player->direction.x = 0;
		data->player->direction.y = -0.5;
		data->player->screen.x = -data->player->direction.y * tan((FOV_IN_DEGREE / 2) * (PI / 180));
		data->player->screen.y = 0;
	}
	else if (data->init_player_dir == 'S')
	{
		data->player->direction.x = 0;
		data->player->direction.y = 0.5;
		data->player->screen.x = -data->player->direction.y * tan((FOV_IN_DEGREE / 2) * (PI / 180));
		data->player->screen.y = 0;
	}
	else if (data->init_player_dir == 'W')
	{
		data->player->direction.x = -0.5;
		data->player->direction.y = 0;
		data->player->screen.x = 0;
		data->player->screen.y = data->player->direction.x * tan((FOV_IN_DEGREE / 2) * (PI / 180));
	}
	else if (data->init_player_dir == 'E')
	{
		data->player->direction.x = 0.5;
		data->player->direction.y = 0;
		data->player->screen.x = 0;
		data->player->screen.y = data->player->direction.x * tan((FOV_IN_DEGREE / 2) * (PI / 180));
	}
}

t_data	*init_data(int argc, char *argv[])
{
	t_data	*data;
	
	if (argc != 2)
	{
		printf("input: './cub3D' 'name_of_map'");
		exit (1);
	}
	data = malloc(sizeof(t_data));
	if (data == NULL)
		ft_error("Memory allocation of data struct failed\n", errno);
	data->screen_width = SCREEN_WIDTH;
	data->screen_height = SCREEN_HEIGHT;
	data->mlx = NULL;
	data->img = NULL;
	data->player = NULL;
	data->ray = NULL;
	data->path_to_the_east_texture = NULL;
	data->path_to_the_west_texture = NULL;
	data->path_to_the_north_texture = NULL;
	data->path_to_the_south_texture = NULL;
	data->time = 0;
	data->prev_time = 0;
	data->map = NULL;
	data->map_height = 0;
	data->map_width = 0;
	data->map_start = 0; // check if needed
	data->init_player_dir = '0';
	data->player_exist = false;
	data->color_ceiling = 0x0;
	data->color_floor = 0x0;
	data->color_ceiling_check = false;
	data->color_floor_check = false;
	parse_map(data, argv);
	init_player(data);
	map_validation(data);
	ft_init_mlx(data);
	return (data);
}
