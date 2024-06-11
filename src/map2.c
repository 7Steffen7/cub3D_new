/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:24:38 by sparth            #+#    #+#             */
/*   Updated: 2024/06/11 16:28:14 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	find_player(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if ((data->map[y][x] == 'N' || data->map[y][x] == 'E'
				|| data->map[y][x] == 'S' || data->map[y][x] == 'W'))
			{
				data->init_player_dir = data->map[y][x];
				data->player->position.x = (double)x;
				data->player->position.y = (double)y;
				data->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
	ft_error_and_free("Invalid Map, No Player found!", 1, data);
}

void	create_map2(t_data *data, char *line, int i, int fd)
{
	while (i < data->map_height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		data->map[i] = (char *)ft_calloc(sizeof(char), (data->map_width + 1));
		if (!data->map[i])
		{
			free(line);
			ft_error_and_free("memory allocation failed", 1, data);
		}
		ft_strllcpy(data->map[i], line, ft_mod_strlen(line) + 1);
		printf("%s\n", data->map[i]);
		line_prep(data->map[i], data->map_width + 1);
		free(line);
		line = NULL;
		i++;
	}
	data->map[i] = NULL;
	if (close(fd) == -1)
		ft_error_and_free("fatal error: close() failed", 1, data);
}

void	create_map(char *file, t_data *data)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_and_free("error opening file", 1, data);
	data->map = (char **)malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
	{
		close(fd);
		ft_error_and_free("memory allocation failed", 1, data);
	}
	get_next_line(-1);
	while (data->map_start--)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		line = NULL;
	}
	create_map2(data, line, i, fd);
}

void	dim_reset(t_data *data)
{
	data->map_start += data->map_height;
	data->map_height = 0;
	data->map_width = 0;
}

void	dim_close_and_check(t_data *data, int fd)
{
	if (close(fd) == -1)
		ft_error_and_free("fatal error: closing the file failed", 1, data);
	if (data->map_start < data->last_color_texture)
		ft_error_and_free("map content always has to be last", 1, data);
}
