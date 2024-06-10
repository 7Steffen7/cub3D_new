/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:08:43 by sparth            #+#    #+#             */
/*   Updated: 2024/06/10 18:31:13 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <string.h>	//

void	find_player(t_data *data)
{
	int	x;
	int	y;
	
	y = 0;
	while(data->map[y])
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
			break;
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
	if( close(fd) == -1)
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
			break;
		free(line);
		line = NULL;
	}
	create_map2(data, line, i, fd);
}

bool	get_dim(t_data *data, int fd, char *line)
{
	
	while (line && !ft_strchr(line, ',') && !ft_strchr(line, '.') && !ft_strchr(line, '/')
		&& !ft_strchr(line, 'C') && !ft_strchr(line, 'F') && !ft_strchr(line, '\t') && !ft_strchr(line, 'f') && ft_strchr(line, '1'))
	{
		if (ft_mod_strlen(line) > data->map_width)
			data->map_width = ft_mod_strlen(line);
		if (ft_strchr(line, 'N') || ft_strchr(line, 'S') || ft_strchr(line, 'W') || ft_strchr(line, 'E'))
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
			break;
		if (!ft_strchr(line, ',') && !ft_strchr(line, '.') && !ft_strchr(line, '/')
			&& !ft_strchr(line, 'C') && !ft_strchr(line, 'F' && !ft_strchr(line, '\t'
			&& (ft_strchr(line, '1')))))
		{
			if (get_dim(data, fd, line))
				break;
			else
				dim_reset(data);
		}
		else
			free(line);
		data->map_start++;
	}
	dim_close_and_check(data, fd);
}

// void	print_map(char **map, t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->map_height)
// 		printf("%s\n", map[i++]);
// }

char	*check_texture(char *line, char *dir, int *error)
{
	int		fd;
	char	*prep_line;
	
	line += 2;
	if (!ft_isspace(*line))
		*error = 12;
	while (ft_isspace(*line))
		line++;
	if (dir)
		*error = 1;
	strcut(line);
	fd = open(line, O_RDONLY);
	if (fd == -1)
		*error = 2;
	if (read(fd, NULL, 0) == -1 && *error != 2)
		*error = 3;
	if (close(fd) == -1 && *error < 2)
		*error = 4;
	prep_line = ft_strdup(line);
	if (!prep_line)
		*error = 5;
	if (*error)
		print_error(error, line);
	return (prep_line);
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
	char **strarr;
	int	i;
	
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

bool	search_textures_colors(t_data *data, int *error, int fd)
{
	char *line;
	
	line = get_next_line(fd);
	if (!line)
		return (false);
	delete_nl(line);
	if (!ft_strncmp(line, "EA", 2))
		data->path_to_the_east_texture = check_texture(line, data->path_to_the_east_texture, error);
	else if (!ft_strncmp(line, "WE", 2))
		data->path_to_the_west_texture = check_texture(line, data->path_to_the_west_texture, error);
	else if (!ft_strncmp(line, "NO", 2))
		data->path_to_the_north_texture = check_texture(line, data->path_to_the_north_texture, error);
	else if (!ft_strncmp(line, "SO", 2))
		data->path_to_the_south_texture = check_texture(line, data->path_to_the_south_texture, error);
	else if (!ft_strncmp(line, "C", 1))
		data->color_ceiling = get_color(data, line, 'C', error);
	else if (!ft_strncmp(line, "F", 1))
		data->color_floor = get_color(data, line, 'F', error);
	free(line);
	line = NULL;
	if (*error)
		return (false);
	return (true);
}

void	get_textures_and_colors(char *file, t_data *data)
{
	int		fd;
	int		error;
	int		i;

	error = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_and_free("error opening file", 1, data);
	i = 0;
	while (1)
	{
		if (!search_textures_colors(data, &error, fd))
			break;
		if (data->path_to_the_east_texture && data->path_to_the_west_texture && data->path_to_the_north_texture
			&& data->path_to_the_south_texture && data->color_ceiling && data->color_floor && data->last_color_texture == 0)
		data->last_color_texture = i;
		i++;
	}
	if (close(fd) == -1)
		ft_error_and_free("fatal error! close failed", 1, data);
	if (!data->path_to_the_east_texture || !data->path_to_the_west_texture || !data->path_to_the_north_texture
		|| !data->path_to_the_south_texture || !data->color_ceiling || !data->color_floor || error)
		ft_error_and_free("textures or colors incomplete / invalid", 1, data);
}

void	parse_map(t_data *data, char *argv[])
{
	get_textures_and_colors(argv[1], data);
	get_dimensions(argv[1], data);
	create_map(argv[1], data);
}
