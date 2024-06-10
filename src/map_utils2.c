/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:56:19 by sparth            #+#    #+#             */
/*   Updated: 2024/06/10 17:29:52 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	line_prep(char *line, int line_len)
{
	int	i;

	i = 0;
	while (i < line_len - 1)
	{
		if (line[i] == ' ' || line[i] == '\0')
			line[i] = '0';
		i++;
	}
	line[i] = '\0';
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
	return (result);
}

bool	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && !ft_isspace(str[i]))
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (false);
		i++;
	}
	return (true);
}
