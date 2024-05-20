/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:08:43 by sparth            #+#    #+#             */
/*   Updated: 2024/05/21 00:43:16 by sparth           ###   ########.fr       */
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

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (i < 24)
		printf("%s\n", map[i++]);
}

void	parse_map(t_data *data, char *argv[])
{
	// int	i;
	// int	j;

	// i = 0;
	// j = 0;
	get_dimensions(argv[1], data);
	create_map(argv[1], data);
	print_map(data->map);
}