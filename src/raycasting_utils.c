/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:54:12 by aweissha          #+#    #+#             */
/*   Updated: 2024/06/09 23:58:09 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	get_lower(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	is_integer(float x)
{
	return (fabsf(x - roundf(x)) < 1e-15);
}

int	ft_pixel(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

float	vector_len(t_vector vector)
{
	return (sqrtf(powf(vector.x, 2) + powf(vector.y, 2)));
}
