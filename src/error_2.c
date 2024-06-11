/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:51:50 by aweissha          #+#    #+#             */
/*   Updated: 2024/06/11 15:00:43 by aweissha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	print_error(int *error, char *line)
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
	return (0);
}

void	error_map_print(char **map, t_data *data)
{
	int	i;
	int	j;

	j = 0;
	printf("\n");
	while (j < data->map_height && map[j])
	{
		i = 0;
		while (map[j][i])
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
