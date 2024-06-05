/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:11:03 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/05 12:39:07 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_coordinates
{
	int		x;
	int		y;
}	t_coordinates;

typedef struct s_map
{
	int		width;
	int		height;
	char	**map;
	t_coordinates	spawn;
}	t_map;

typedef struct s_data
{
	t_map			*map;
	uint32_t		ceiling_color;
	uint32_t		floor_color;
	mlx_texture_t	*n_texture;
	mlx_texture_t	*s_texture;
	mlx_texture_t	*w_texture;
	mlx_texture_t	*e_texture;
}	t_data;

# include "libs42/libs42.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>


void		parse(t_data *data, char *path);
void		parse_texture(t_data *data, int fd, char *line, int *t_count);
void		parse_color(t_data *data, int fd, char *line, int *c_count);
void		parse_map(t_data *data, int fd);
void		parse_error(t_data *data, int fd, char *msg);

#endif