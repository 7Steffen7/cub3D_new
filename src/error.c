/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:11:02 by aweissha          #+#    #+#             */
/*   Updated: 2024/05/21 18:07:04 by aweissha         ###   ########.fr       */
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
}

void	free_everything(t_data *data)
{
	free_textures(data);
	mlx_terminate(data->mlx);
	free(data->player);
	free(data->ray);
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
