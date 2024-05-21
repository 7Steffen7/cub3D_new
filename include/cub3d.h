/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sparth <sparth@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:02:00 by aweissha          #+#    #+#             */
/*   Updated: 2024/05/21 13:46:16 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <float.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

// # define MAP_WIDTH 24
// # define MAP_HEIGHT 24
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define WALL_DIST 0.25
# define FOV_IN_DEGREE 60
# define PI 3.14159265358979

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_player
{
	t_vector	position;
	t_vector	direction;
	t_vector	screen;
}	t_player;

typedef struct s_ray
{
	int			index;
	t_vector	start_pos;
	t_vector	pos;
	t_vector	dir;
	float		factor;
	int			map_x;
	int			map_y;
	char		wall;
	int			side;
	double		perp_length;
	int			line_height;
	int			line_bottom;
	int			line_top;
}	t_ray;

typedef struct s_data
{
	int			screen_width;
	int			screen_height;
	int			map_width;
	int			map_height;
	char		init_player_dir;
	char		**map;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	*player;
	t_ray		*ray;
	double		time;
	double		prev_time;
}	t_data;

// init.c
void	init_ray(int ray_index, t_data *data);
void	ft_init_mlx(t_data *data);
void	init_player(t_data *data);
t_data	*init_data(int argc, char *argv[]);

// error.c
void	free_everything(t_data *data);
void	ft_error(char *message, int code);
void	ft_mlx_error(const char *message, int code);
void	ft_mlx_error_and_free(const char *message, int code, t_data *data);
void	ft_error_and_free(char *message, int code, t_data *data);

// raycasting.c
double	get_lower(double a, double b);
double	find_factor(t_ray *ray);
void	elongate_ray(t_ray *ray);
int 	is_integer(double x);
void	check_side(t_data *data);
void	check_for_wall(t_data *data);
double	vector_len(t_vector vector);
void	calc_perp_length(t_data *data);
void	ray_algorithm(t_data *data);
void	line_to_image(t_data *data);
void	render_image(t_data *data);
void	raycaster(t_data *data);

// map.c
void	parse_map(t_data *data, char *argv[]);
void	find_player(t_data *data);


#endif