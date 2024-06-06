/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:11:03 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/06 10:54:48 by niklasburch      ###   ########.fr       */
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

# define WIDTH 2000
# define HEIGHT 1000

typedef struct s_coordinates
{
	float		x;
	float		y;
}	t_coordinates;

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
	t_map			*map;
	t_player		player;
	float			scale;
	uint32_t		ceiling_color;
	uint32_t		floor_color;
	mlx_texture_t	*n_texture;
	mlx_texture_t	*s_texture;
	mlx_texture_t	*w_texture;
	mlx_texture_t	*e_texture;
}	t_data;

/*PARSING*/
void		parse(t_data *data, char *path);
void		parse_texture(t_data *data, int fd, char *line, int *t_count);
void		parse_color(t_data *data, int fd, char *line, int *c_count);
void		parse_map(t_data *data, char *path, int fd);
bool		check_map(t_data *data);
bool		allocate_map(t_data *data, char ***allocate_to);
void		parse_error(t_data *data, int fd, char *msg);

/*GRAPHICS*/
void		render_map(t_data *data);
void		render_player(t_data *data);
void		reset_image(mlx_image_t *image, mlx_t *mlx, int color);

/*HOOKS*/
void		keyhook(mlx_key_data_t keydata, void *param);

/*DEBUG*/
void		print_data(t_data *data);

#endif
