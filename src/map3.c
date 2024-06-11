/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:29:58 by sparth            #+#    #+#             */
/*   Updated: 2024/06/11 16:31:16 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	get_dim(t_data *data, int fd, char *line)
{
	while (line && !ft_strchr(line, ',') && !ft_strchr(line, '.')
		&& !ft_strchr(line, '/') && !ft_strchr(line, 'C')
		&& !ft_strchr(line, 'F') && !ft_strchr(line, '\t')
		&& !ft_strchr(line, 'f') && ft_strchr(line, '1'))
	{
		if (ft_mod_strlen(line) > data->map_width)
			data->map_width = ft_mod_strlen(line);
		if (ft_strchr(line, 'N') || ft_strchr(line, 'S')
			|| ft_strchr(line, 'W') || ft_strchr(line, 'E'))
		{
			if (data->player_exist == true)
			{
				close (fd);
				free(line);
				ft_error_and_free("only one player is valid!", 1, data);
			}
			else
				data->player_exist = true;
		}
		data->map_height++;
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	return (data->player_exist);
}

void	get_dimensions(char *file, t_data *data)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_and_free("error opening file", 1, data);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!ft_strchr(line, ',') && !ft_strchr(line, '.')
			&& !ft_strchr(line, '/') && !ft_strchr(line, '\t')
			&& (ft_strchr(line, '1')))
		{
			if (get_dim(data, fd, line))
				break ;
			else
				dim_reset(data);
		}
		else
			free(line);
		data->map_start++;
	}
	dim_close_and_check(data, fd);
}

void	get_color_prep(t_data *data, char color, int *error)
{
	if (color == 'C')
	{
		if (data->color_ceiling_check == true)
			*error = 6;
		else
			data->color_ceiling_check = true;
	}
	if (color == 'F')
	{
		if (data->color_floor_check == true)
			*error = 6;
		else
			data->color_floor_check = true;
	}
}

unsigned int	get_color2(char **strarr, int *error, int i)
{
	int	red;
	int	blue;
	int	green;

	if (*error == 0 && i != 3)
		*error = 9;
	else if (*error == 0 && i == 3)
	{
		blue = ft_atoi(strarr[2]);
		green = ft_atoi(strarr[1]);
		red = ft_atoi(strarr[0]);
	}
	if (*error == 0 && (blue > 255 || green > 255 || red > 255))
		*error = 8;
	while (strarr[i--])
		free(strarr[i]);
	if (strarr)
		free(strarr);
	if (*error)
		return (print_error(error, NULL));
	return (color_calc(red, green, blue));
}

unsigned int	get_color(t_data *data, char *line, char color, int *error)
{
	char	**strarr;
	int		i;

	get_color_prep(data, color, error);
	++line;
	if (!ft_isspace(*line))
		*error = 7;
	while (ft_isspace(*line))
		line++;
	strarr = ft_split(line, ',');
	if (!strarr)
		*error = 5;
	i = 0;
	while (strarr[i])
	{
		if (ft_strcheck(strarr[i]) > 3 && *error == 0)
			*error = 8;
		if (!ft_isnum(strarr[i]))
			*error = 11;
		i++;
	}
	return (get_color2(strarr, error, i));
}
