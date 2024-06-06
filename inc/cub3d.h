/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:11:03 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/06 02:18:36 by niklasburch      ###   ########.fr       */
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

# define WIDTH 1200
# define HEIGHT 1000

typedef struct s_coordinates
{
	int		x;
	int		y;
}	t_coordinates;

typedef struct s_map
{
	int				width;
	int				height;
	char			**map;
	t_coordinates	spawn;
}	t_map;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_map			*map;
	uint32_t		ceiling_color;
	uint32_t		floor_color;
	mlx_texture_t	*n_texture;
	mlx_texture_t	*s_texture;
	mlx_texture_t	*w_texture;
	mlx_texture_t	*e_texture;
}	t_data;

void		parse(t_data *data, char *path);
void		parse_texture(t_data *data, int fd, char *line, int *t_count);
void		parse_color(t_data *data, int fd, char *line, int *c_count);
void		parse_map(t_data *data, char *path, int fd);
bool		allocate_map(t_data *data, char ***allocate_to);
bool		check_map(t_data *data);
void		parse_error(t_data *data, int fd, char *msg);
void		print_data(t_data *data);

#endif
