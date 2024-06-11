/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:11:02 by aweissha          #+#    #+#             */
/*   Updated: 2024/06/11 15:06:47 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->textures[i])
			mlx_delete_texture(data->textures[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (data->weapon_textures[i])
			mlx_delete_texture(data->weapon_textures[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (data->weapon_shot_textures[i])
			mlx_delete_texture(data->weapon_shot_textures[i]);
		i++;
	}
	if (data->door_texture[0])
		mlx_delete_texture(data->door_texture[0]);
}

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	if (data->map)
	{
		while (data->map[i])
			free(data->map[++i]);
		free (data->map);
	}
}

void	free_everything(t_data *data)
{
	free_textures(data);
	if (data->mlx)
		mlx_terminate(data->mlx);
	if (data->player)
		free(data->player);
	if (data->ray)
		free(data->ray);
	if (data->path_to_the_east_texture)
		free(data->path_to_the_east_texture);
	if (data->path_to_the_north_texture)
		free(data->path_to_the_north_texture);
	if (data->path_to_the_south_texture)
		free(data->path_to_the_south_texture);
	if (data->path_to_the_west_texture)
		free(data->path_to_the_west_texture);
	free_map(data);
	if (data)
		free(data);
}

void	ft_error(const char *message, int code)
{
	write(2, message, ft_strlen(message));
	exit(code);
}

void	ft_error_and_free(const char *message, int code, t_data *data)
{
	free_everything(data);
	ft_error(message, code);
}
