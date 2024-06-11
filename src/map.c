/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:08:43 by sparth            #+#    #+#             */
/*   Updated: 2024/06/11 16:32:32 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

bool	search_textures_colors(t_data *data, int *error, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (false);
	delete_nl(line);
	if (!ft_strncmp(line, "EA", 2))
		data->ea_texture = check_texture(line, data->ea_texture, error);
	else if (!ft_strncmp(line, "WE", 2))
		data->we_texture = check_texture(line, data->we_texture, error);
	else if (!ft_strncmp(line, "NO", 2))
		data->no_texture = check_texture(line, data->no_texture, error);
	else if (!ft_strncmp(line, "SO", 2))
		data->so_texture = check_texture(line, data->so_texture, error);
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
			break ;
		if (data->ea_texture && data->we_texture && data->no_texture
			&& data->so_texture && data->color_ceiling && data->color_floor
			&& data->last_color_texture == 0)
			data->last_color_texture = i;
		i++;
	}
	if (close(fd) == -1)
		ft_error_and_free("fatal error! close failed", 1, data);
	if (!data->ea_texture || !data->we_texture || !data->no_texture
		|| !data->so_texture || !data->color_ceiling || !data->color_floor
		|| error)
		ft_error_and_free("textures or colors incomplete / invalid", 1, data);
}

void	parse_map(t_data *data, char *argv[])
{
	get_textures_and_colors(argv[1], data);
	get_dimensions(argv[1], data);
	create_map(argv[1], data);
}
