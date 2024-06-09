/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:11:02 by aweissha          #+#    #+#             */
/*   Updated: 2024/06/09 15:18:14 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_error(int *error, char *line)
{
	if (*error == 1)
		printf("Invalid file! Conflict between texture files\n");
	if (*error == 2)
		printf("Error opening file: %s\n", line);
	if (*error == 3)
		printf("Permission denied: %s\n", line);
	if (*error == 4)
		printf("fatal error! closing %s failed\n", line);
	if (*error == 5)
		printf("fatal error: memory allocation failed\n");
	if (*error == 6)
		printf("Color error! Only one color for floor and one for ceiling accepted\n");
	if (*error == 7)
		printf("color indication and value must be seperated example: 'C 255,255,255'\n");
	if (*error == 8)
		printf("numbers too large - expected rgb input 0-255 -> '255,255,255'\n");
	if (*error == 9)
		printf("color syntax wrong - expected rgb input 0-255 -> '255,255,255'\n");
	if (*error == 10)
		printf("\n");
	if (*error == 11)
		printf("color input should be numeric and seperated be commas\n");
	if (*error == 12)
		printf("texture indication and file must be seperated! example: 'EA file.png'\n");
}

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
}

void	free_everything(t_data *data)
{
	int	i;

	i = 0;
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
	if (data->map)
	{		
		while (data->map[i])
			free(data->map[++i]);
		free (data->map);
	}
	if (data)
		free(data);
}

void	ft_error(char *message, int code)
{
	perror(message);
	exit(code);
}

void	ft_mlx_error(const char *message, int code)
{
	fprintf(stderr, "%s\n", message);
	exit(code);
}

void	ft_mlx_error_and_free(const char *message, int code, t_data *data)
{
	free_everything(data);
	ft_mlx_error(message, code);
}

void	ft_error_and_free(char *message, int code, t_data *data)
{
	free_everything(data);
	ft_error(message, code);
}
