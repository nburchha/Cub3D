/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:11:03 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/22 19:33:14 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "libs42/libs42.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>

# define WIDTH 2048
# define HEIGHT 1024
# define PIXEL_SIZE 64.0f
# define M_SCALE (PIXEL_SIZE / 4.0)
# define FOV 60
# define MOVE_SPEED 5.0f
# define ROTATE_SPEED 0.1f
# define MAX_KEY 341
# define BONUS 1
# define DOOR_PATH "textures/dirt_podzol_side.png"
# define SPRITE_PATH "textures/deagle1056x648.png"

# define FLOOR '0'
# define WALL '1'
# define DOOR '2'
# define OPEN_DOOR '3'

typedef struct s_coordinates
{
	float		x;
	float		y;
}	t_coordinates;

typedef struct s_dda
{
	float			angle;

	float			start_x;
	float			start_y;

	float			delta_x;
	float			delta_y;

	float			end_x;
	float			end_y;

	float			len;

	int				step_direction_x;
	int				step_direction_y;

	char			wall_face;
	int				texture;

	int				is_open_door;
	float			door_end_x;
	float			door_end_y;
}				t_dda;

typedef struct s_map
{
	int				width;
	int				height;
	char			**map;
	t_coordinates	spawn;
}	t_map;

typedef struct s_player
{
	t_coordinates	pos;
	float			dir;
}	t_player;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_image_t		*minimap;
	mlx_image_t		*deagle;
	mlx_texture_t	*sprite_texture;
	t_map			*map;
	t_player		player;
	float			scale;
	bool			keys[MAX_KEY];
	uint32_t		ceiling_color;
	uint32_t		floor_color;
	mlx_texture_t	*n_texture;
	mlx_texture_t	*s_texture;
	mlx_texture_t	*w_texture;
	mlx_texture_t	*e_texture;
	mlx_texture_t	*door_texture;
}	t_data;

/*PARSING*/
void		parse(t_data *data, char *path);
bool		parse_texture(t_data *data, int fd, char *line, int *t_count);
bool		parse_color(t_data *data, int fd, char *line, int *c_count);
void		parse_map(t_data *data, char *path, int fd);
bool		check_map(t_data *data);
bool		allocate_map(t_data *data, char ***allocate_to);
void		parse_error(t_data *data, int fd, char *msg);

/*GRAPHICS*/
void		render_map(t_data *data);
void		render_player(t_data *data);
void		draw_minimap(t_data *data);
void		animate_sprite(t_data *data, mlx_image_t *img);
void		reset_image(mlx_image_t *image, int color);
float		normalize_angle(float angle);
void		reset_canvas(t_data *data);

void		draw_block(t_data *data, int coords[2], int size, uint32_t color);
void		draw_line(t_coordinates start, t_coordinates end, uint32_t color, \
					mlx_image_t *img);
void		draw_circle(float coords[2], float radius, uint32_t color, mlx_image_t *img);
void		draw_triangle(t_data *data, float direction, uint32_t color);
bool		valid_coords(t_data *data, int x, int y);
int			get_color_texture(mlx_texture_t *texture, int x, int y);

/*PLAYER*/
void		dda_algo(t_dda *dda, t_data *data, float angle);
void		movement(t_data *data);
bool		wall_collision(t_data *data, const char direction, const char xy);


/*HOOKS*/
void		keyhook(mlx_key_data_t keydata, void *param);
void		general_hook(void *param);
void		cursor_hook(double x, double y, void *param);

/*DEBUG*/
void		print_data(t_data *data);

#endif
