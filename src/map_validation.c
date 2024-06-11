/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:34:46 by sparth            #+#    #+#             */
/*   Updated: 2024/06/11 15:21:46 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	flood_fill(char **map, t_cord dim, t_cord cur, char fill_chr)
{
	if (cur.y < 0 || cur.y >= dim.y
		|| cur.x < 0 || cur.x >= dim.x || (map[cur.y][cur.x] != fill_chr))
		return ;
	map[cur.y][cur.x] = 'f';
	flood_fill(map, dim, (t_cord){cur.x - 1, cur.y}, fill_chr);
	flood_fill(map, dim, (t_cord){cur.x + 1, cur.y}, fill_chr);
	flood_fill(map, dim, (t_cord){cur.x, cur.y - 1}, fill_chr);
	flood_fill(map, dim, (t_cord){cur.x, cur.y + 1}, fill_chr);
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
	while (i < data->map_height - 1)
	{
		if (map[i][0] == 'f' || map[i][data->map_width - 1] == 'f')
		{
			error_map_print(map, data);
			ft_error_and_free("map is not closed!", 1, data);
		}
		i++;
	}
}

void	map_prep(char *map, bool *error)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] != '1' && map[i] != '0' && map[i] != ' ' && map[i] != 'D'
			&& map[i] != 'N' && map[i] != 'S' && map[i] != 'E' && map[i] != 'W')
			*error = true;
		if (map[i] != '1')
			map[i] = '0';
		i++;
	}
}

void	map_free_and_check(char **map, bool error, t_data *data, int i)
{
	check_if_valid(map, data);
	while (i--)
		free(map[i]);
	free(map);
	if (error == true)
	{
		printf("map contains invalid chars: FLOOR: 0 WALL: 1 ");
		ft_error_and_free("PLAYER DIR: N S W E DOOR: D\n", 1, data);
	}
}

void	map_validation(t_data *data)
{
	t_cord		start;
	t_cord		dim;
	char		**map;
	int			i;
	bool		error;

	error = false;
	start.x = (int)data->player->position.x;
	start.y = (int)data->player->position.y;
	dim = (t_cord){data->map_width, data->map_height};
	map = (char **)malloc(sizeof(char *) * data->map_height + 1);
	if (!map)
		ft_error_and_free("malloc failed!", 1, data);
	i = 0;
	while (i < data->map_height)
	{
		map[i] = ft_strdup(data->map[i]);
		if (!map[i])
			ft_error_and_free("ft_strdup failed!", 1, data);
		map_prep(map[i++], &error);
	}
	flood_fill(map, dim, start, map[start.y][start.x]);
	map_free_and_check(map, error, data, i);
}
