/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aweissha <aweissha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:02:00 by aweissha          #+#    #+#             */
/*   Updated: 2024/06/11 16:32:11 by sparth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>
# include <sys/time.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

# define MINIMAP_WIDTH 20
# define MINIMAP_HEIGHT 16
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define WALL_DIST 0.25
# define FOV_IN_DEGREE 60
# define PI 3.14159265358979
# define WALL_COLOR_MAP 0xFFFFEBFF
# define DOOR_COLOR_MAP 0x808080FF

typedef struct s_block
{
	int				start_x;
	int				start_y;
	int				j;
	int				k;
	int				pivot_x;
	int				pivot_y;
	float			theta;
	unsigned int	color;
}	t_block;

typedef struct s_cord
{
	int	x;
	int	y;
}	t_cord;

typedef struct s_vector
{
	float	x;
	float	y;
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
	double		perp_length;
	int			side;
	float		wall_x;
	int			tex_x;
	int			tex_y;
	int			line_height;
	int			line_bottom;
	int			line_top;
}	t_ray;

typedef struct s_data
{
	int				screen_width;
	int				screen_height;
	int				map_width;
	int				map_height;
	int				map_start;
	bool			player_exist;
	char			init_player_dir;
	char			**map;
	mlx_texture_t	*textures[4];
	mlx_texture_t	*door_texture[1];
	mlx_texture_t	*weapon_textures[3];
	mlx_texture_t	*weapon_shot_textures[3];
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		*player;
	t_ray			*ray;
	long			time;
	char			*ea_texture;
	char			*we_texture;
	char			*no_texture;
	char			*so_texture;
	unsigned int	color_ceiling;
	unsigned int	color_floor;
	bool			color_ceiling_check;
	bool			color_floor_check;
	int				weapon;
	int				weapon_shot;
	int				mouse_temp_x;
	int				mouse_temp_y;
	int				last_color_texture;
	bool			mouse;
}	t_data;

// init.c
void			init_ray(int ray_index, t_data *data);
void			ft_init_mlx(t_data *data);
void			init_player(t_data *data);
void			init_textures(t_data *data);
t_data			*init_data(int argc, char *argv[]);

// init_2.c
void	init_ray_2(t_data *data);
void	init_textures_2(t_data *data);
void	init_data_textures(t_data *data);
void	init_data_params(t_data *data);
void	player_dir_init(t_data *data, float x, float y, char dir);


// error.c
void			free_textures(t_data *data);
void			free_map(t_data *data);
void			free_everything(t_data *data);
void			ft_error(const char *message, int code);
void			ft_error_and_free(const char *message, int code, t_data *data);

// error_2.c
int				print_error(int *error, char *line);
void			error_map_print(char **map, t_data *data);

// ray_algorithm.c
double			find_factor(t_ray *ray);
void			elongate_ray(t_ray *ray);
void			check_for_wall(t_data *data);
void			calc_perp_length(t_data *data);

// raycasting.c
void			ray_algorithm(t_data *data);
void			raycaster(t_data *data);

// raycasting_utils.c
double			get_lower(double a, double b);
int				is_integer(float x);
int				ft_pixel(int r, int g, int b, int a);
float			vector_len(t_vector vector);

// render.c
void			fill_repeating_pixels(int *counter, int color, t_data *data);
void			line_to_image(t_data *data);
void			render_image(t_data *data);

// textures.c
void			check_side(t_ray *ray);
void			calc_texture(t_data *data);
void			calc_tex_y(int counter, mlx_texture_t *texture, t_data *data);
int				find_color_from_texture(int counter, t_data *data);

// weapon.c
unsigned int	find_weapon_color(float x, float y, t_data *data);
void			add_weapon(t_data *data);

// map.c
void			parse_map(t_data *data, char *argv[]);
void			find_player(t_data *data);
void			print_map(char **map, t_data *data);

//map2.c
void	find_player(t_data *data);
void	create_map2(t_data *data, char *line, int i, int fd);
void	create_map(char *file, t_data *data);
void	dim_reset(t_data *data);
void	dim_close_and_check(t_data *data, int fd);

//map3.c
bool			get_dim(t_data *data, int fd, char *line);
void			get_dimensions(char *file, t_data *data);
void			get_color_prep(t_data *data, char color, int *error);
unsigned int	get_color2(char **strarr, int *error, int i);
unsigned int	get_color(t_data *data, char *line, char color, int *error);


//map_utils.c
int				ft_mod_strlen(const char *s);
size_t			ft_strllcpy(char *dst, const char *src, size_t dstsize);
bool			ft_isspace(char c);
int				ft_strcheck(char *str);
void			strcut(char *str);

//map_utils2.c
void			line_prep(char *line, int line_len);
void			delete_nl(char *line);
unsigned int	color_calc(int red, int green, int blue);
bool			ft_isnum(char *str);

// map_validation.c
void			map_validation(t_data *data);

// mini_map.c
void			mini_map(t_data *data);
void			map_ray(t_data *data, int index, double perp_len);

//mini_map2.c
void	draw_arrow(t_data *data);

//player_movement.c
void			player_movement(t_data *data, int mouse_x, int mouse_y);
void			player_vertical_movement(t_data *data, float speed);
void			player_rotation(t_data *data, int speed);
void			player_horizontal_movement(t_data *data, float speed);
bool			able_2_walk(char **map, double y, double x);

#endif