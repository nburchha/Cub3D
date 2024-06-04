/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:11:03 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/04 22:13:59 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H

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
	t_map	*map;
}	t_data;

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>


t_data		parse(char *path);
int			parse_map(t_map *map, char *line);

#endif