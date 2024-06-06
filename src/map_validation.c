/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:34:46 by sparth            #+#    #+#             */
/*   Updated: 2024/06/07 00:00:35 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	flood_fill(char **map, t_cord dim, t_cord cur, char fill_chr)
{
	if (cur.y < 0 || cur.y >= dim.y
		|| cur.x < 0 || cur.x >= dim.x || map[cur.y][cur.x] != fill_chr)
		return ;
	map[cur.y][cur.x] = 'f';
	flood_fill(map, dim, (t_cord){cur.x - 1, cur.y}, fill_chr);
	flood_fill(map, dim, (t_cord){cur.x + 1, cur.y}, fill_chr);
	flood_fill(map, dim, (t_cord){cur.x, cur.y - 1}, fill_chr);
	flood_fill(map, dim, (t_cord){cur.x, cur.y + 1}, fill_chr);
}

void	error_map_print(char **map, t_data *data)
{
	int	i;
	int	j;

	j = 0;
	printf("\n");
	while(j < data->map_height && map[j])
	{
		i = 0;
		while(map[j][i])
		{
			if (map[j][i] == 'f')
				printf("\033[0;31mf\033[0m");
			else
				printf("%c", map[j][i]);
			i++;
		}
		free(map[j]);
		printf("\n");
		j++;
	}
	printf("\n");
	if (map)
		free(map);
}

void	check_if_valid(char **map, t_data *data)
{
	int	i;

	i = 1;
	if (ft_strchr(map[0], 'f') || ft_strchr(map[data->map_height - 1], 'f'))
	{
		error_map_print(map, data);
		ft_error_and_free("map is not closed!", 1, data);
	}
	while(i < data->map_height - 1)
	{
		if (map[i][0] == 'f' || map[i][data->map_width - 1] == 'f')
		{
			error_map_print(map, data);
			ft_error_and_free("map is not closed!", 1, data);
		}
		i++;
	}
	
}

void	map_validation(t_data *data)
{
	t_cord		start;
	t_cord		dim;
	char		**map;
	int			i;
	
	start.x = (int)data->player->position.x;
	start.y = (int)data->player->position.y;
	dim.x = data->map_width;
	dim.y = data->map_height;
	map = (char **)malloc(sizeof(char *) * data->map_height + 1);
	if (!map)
		ft_error_and_free("malloc failed!", 1, data);
	i = 0;
	while (i < data->map_height)
	{
		map[i] = ft_strdup(data->map[i]);
		if (!map[i])
			ft_error_and_free("ft_strdup failed!", 1, data);
		i++;
	}
	// map[i] = NULL;
	// printf("\n");
	// printf("dim x: %d\n", dim.x);
	// printf("dim y: %d\n", dim.y);
	// printf("player x: %d\n", start.x);
	// printf("player y: %d\n", start.y);
	map[start.y][start.x] = '0';
	// print_map(map, data);
	flood_fill(map, dim, start, map[start.y][start.x]);
	// printf("\n");
	// print_map(map, data);
	check_if_valid(map, data);
	while (i--)
		free(map[i]);
	free(map);
}
