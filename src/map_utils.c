/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:50:09 by sparth            #+#    #+#             */
/*   Updated: 2024/06/11 14:27:04 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

bool	ft_isspace(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (true);
	return (false);
}

int	ft_strcheck(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i + count] && !ft_isspace(str[i + count]))
		count++;
	return (count);
}

void	strcut(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (ft_isspace(str[--len]))
		str[len] = '\0';
}
