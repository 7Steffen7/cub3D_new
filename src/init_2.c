/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:45:55 by aweissha          #+#    #+#             */
/*   Updated: 2024/06/11 15:39:48 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_ray_2(t_data *data)
{
	t_ray	*ray;

	ray = data->ray;
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

void	init_textures_2(t_data *data)
{
	data->weapon_shot_textures[0] = mlx_load_png("./textures/gun_shot.png");
	if (!(data->weapon_shot_textures[0]))
		ft_error_and_free("mlx_load_png failed\n", mlx_errno, data);
	data->weapon_shot_textures[1] = mlx_load_png("./textures/gun_2_shot.png");
	if (!(data->weapon_shot_textures[1]))
		ft_error_and_free("mlx_load_png failed\n", mlx_errno, data);
	data->weapon_shot_textures[2] = mlx_load_png("./textures/knive_stab.png");
	if (!(data->weapon_shot_textures[2]))
		ft_error_and_free("mlx_load_png failed\n", mlx_errno, data);
	data->door_texture[0] = mlx_load_png("./textures/door.png");
	if (!(data->door_texture[0]))
		ft_error_and_free("mlx_load_png failed\n", mlx_errno, data);
}

void	init_data_textures(t_data *data)
{
	data->textures[0] = NULL;
	data->textures[1] = NULL;
	data->textures[2] = NULL;
	data->textures[3] = NULL;
	data->door_texture[0] = NULL;
	data->weapon_textures[0] = NULL;
	data->weapon_textures[1] = NULL;
	data->weapon_textures[2] = NULL;
	data->weapon_shot_textures[0] = NULL;
	data->weapon_shot_textures[1] = NULL;
	data->weapon_shot_textures[2] = NULL;
}

void	init_data_params(t_data *data)
{
	data->screen_width = SCREEN_WIDTH;
	data->screen_height = SCREEN_HEIGHT;
	data->map_width = 0;
	data->map_height = 0;
	data->map_start = 0;
	data->player_exist = false;
	data->init_player_dir = '0';
	data->time = 0;
	data->path_to_the_east_texture = NULL;
	data->path_to_the_west_texture = NULL;
	data->path_to_the_north_texture = NULL;
	data->path_to_the_south_texture = NULL;
	data->color_ceiling = 0x0;
	data->color_floor = 0x0;
	data->color_ceiling_check = false;
	data->color_floor_check = false;
	data->weapon = -1;
	data->weapon_shot = -1;
	data->mouse_temp_x = 512;
	data->mouse_temp_y = 384;
	data->last_color_texture = 0;
	data->mouse = false;
}
