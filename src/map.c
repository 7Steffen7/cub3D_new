/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:08:43 by sparth            #+#    #+#             */
/*   Updated: 2024/05/23 01:02:13 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <string.h>	//

int	ft_mod_strlen(const char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}

size_t	ft_strllcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_i;

	src_i = 0;
	if (dstsize == 0)
	{
		while (src[src_i])
			src_i++;
		return (src_i);
	}
	while (src_i < dstsize - 1 && src[src_i] != '\0' && src[src_i] != '\n')
	{
		dst[src_i] = src[src_i];
		src_i++;
	}
	dst[src_i] = '\0';
	while (src[src_i] != '\0')
		src_i++;
	return (src_i);
}

void	free_and_exit_map(char **map, int i)
{
	while (i--)
		free(map[i]);
	if (map)
		free(map);
	printf("memory allocation failed\n");
	exit (1);
}

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
				|| data->map[y][x] == 'S' || data->map[y][x] == 'W') && ft_isdigit(data->map[y][x + 1]))
			{
				data->init_player_dir = data->map[y][x];
				data->player->position.x = (double)x;
				data->player->position.y = (double)y;
				return ;
			}
			x++;
		}
		y++;
	}
	printf("Invalid Map, No Player found\n");
	exit (1);
}

void	create_map(char *file, t_data *data)
{
	char	*line;
	// char	**map;
	int		fd;
	int		line_len;
	int		i;
	
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("error opening file\n");
		exit (1);
	}
	data->map = (char **)malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
	{
		printf("memory allocation failed\n");
		exit (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		line_len = ft_mod_strlen(line);
		data->map[i] = (char *)malloc(sizeof(char) * (line_len + 1));
		if (!data->map[i])
		{
			free(line);
			free_and_exit_map(data->map, i);
		}
		ft_strllcpy(data->map[i], line, ft_mod_strlen(line) + 1);
		free(line);
		line = NULL;
		i++;
	}
	data->map[i] = NULL;
	close(fd);
}

void	get_dimensions(char *file, t_data *data)
{
	int		fd;
	char	*line;
	// int		temp;
	
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("error opening file\n");
		exit (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		// if ()
		if (ft_mod_strlen(line) > data->map_width)
			data->map_width = ft_mod_strlen(line);
		free(line);
		line = NULL;
		data->map_height++;
	}
	if (close(fd) == -1)
	{
		printf("fatal error: closing the file failed\n");
		exit (1);
	}
}

void	print_map(char **map, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_height)
		printf("%s\n", map[i++]);
}
void	delete_nl(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
}

char	*check_texture(char *line, char *dir)
{
	int		fd;
	ssize_t	bytes_read;
	char	buffer[1];
	char	*prep_line;
	
	line = line + 3;
	delete_nl(line);
	if (dir)
	{
		//free stuff
		printf("Invalid file! Conflict between texture files\n");
		exit (1);
	}
	fd = open(line, O_RDONLY);
	if (fd == -1)
	{
		//free stuff
		printf("Error opening %s\n", line);
		exit (1);
	}
	bytes_read = read(fd, buffer, 1);
	if (bytes_read == -1)
	{
		//free stuff
		printf("Permission denied: %s\n", line);
		exit (1);
	}
	if (close(fd) == -1)
	{
		//free stuff
		printf("fatal error! closing %s failed\n", line);
		exit (1);
	}
	prep_line = ft_strdup(line);
	return (prep_line);
}

unsigned int	color_calc(int red, int green, int blue)
{
	unsigned int	result;
	int				transparent;

	transparent = 255;
	result = red;
	result *= 256;
	result += green;
	result *= 256;
	result += blue;
	result *= 256;
	result += transparent;
	// result *= 256;
	return (result);
}

unsigned int	get_color(char *line, bool check_if_double)
{
	char **strarr;
	int	red;
	int	blue;
	int	green;
	int	i;
	
	i = 0;
	if (check_if_double == true)
	{
		//free stuff
		printf("Color error! Only one color for floor and one for ceiling accepted\n");
		exit (1);
	}
	line = line + 2;
	strarr = ft_split(line, ',');
	while (strarr[i])
	{
		if (ft_strlen(strarr[i]) > 3)
		{
			//free stuff
			printf("numbers too large - expected rgb input 0-255 -> '255,255,255'\n");
			exit (1);
		}
		i++;
	}
	if (i != 3)
	{
		//free stuff
		printf("color syntax wrong - expected rgb input 0-255 -> '255,255,255'\n");
		exit (1);
	}
	blue = ft_atoi(strarr[2]);
	green = ft_atoi(strarr[1]);
	red = ft_atoi(strarr[0]);
	if (blue > 255 || green > 255 || red > 255)
	{
		printf("numbers too large - expected rgb input 0-255 -> '255,255,255'\n");
		exit (1);
	}
	while (strarr[i--])
		free(strarr[i]);
	if (strarr)
		free(strarr);
	return (color_calc(red, green, blue));
	// next step save checked value to hexa value in struct;
}

void	get_textures_and_colors(char *file, t_data *data)
{
	int			fd;
	char		*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("error opening file\n");
		exit (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (!ft_strncmp(line, "EA ", 3))
			data->path_to_the_east_texture = check_texture(line, data->path_to_the_east_texture);
		else if (!ft_strncmp(line, "WE ", 3))
			data->path_to_the_west_texture = check_texture(line, data->path_to_the_west_texture);
		else if (!ft_strncmp(line, "NO ", 3))
			data->path_to_the_north_texture = check_texture(line, data->path_to_the_north_texture);
		else if (!ft_strncmp(line, "SO ", 3))
			data->path_to_the_south_texture = check_texture(line, data->path_to_the_south_texture);
		else if (!ft_strncmp(line, "C ", 2))
			data->color_ceiling = get_color(line, data->color_ceiling_check);
		else if (!ft_strncmp(line, "F ", 2))
			data->color_floor = get_color(line, data->color_floor_check);
			
		free(line);
		line = NULL;
	}
	// check close
	// check if every texture and color is given
	close (fd);
	printf("color ceiling: %u\n", data->color_ceiling);
	printf("color floor: %u\n", data->color_floor);
	// printf("path_east: %s\n", data->path_to_the_east_texture);
	// printf("path_west: %s\n", data->path_to_the_west_texture);
	// printf("path_north: %s\n", data->path_to_the_north_texture);
	// printf("path_south: %s\n", data->path_to_the_south_texture);
}

void	parse_map(t_data *data, char *argv[])
{
	get_textures_and_colors(argv[1], data);
	get_dimensions(argv[1], data);
	create_map(argv[1], data);
	print_map(data->map, data);
}