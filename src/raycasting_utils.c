/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:54:12 by aweissha          #+#    #+#             */
/*   Updated: 2024/06/09 16:32:53 by aweissha         ###   ########.fr       */
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

int	is_integer(double x)
{
	return (fabs(x - round(x)) < 1e-15);
}

int	ft_pixel(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

double	vector_len(t_vector vector)
{
	return (sqrt(pow(vector.x, 2) + pow(vector.y, 2)));
}
