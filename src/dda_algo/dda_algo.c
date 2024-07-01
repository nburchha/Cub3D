/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:07:05 by psanger           #+#    #+#             */
/*   Updated: 2024/07/01 23:31:17 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_dir(double rad, int *step_dir_x, int *step_dir_y)
{
	if (rad >= 0 && rad <= M_PI / 2)
	{
		*step_dir_x = 1;
		*step_dir_y = -1;
	}
	if (rad >= M_PI / 2 && rad <= M_PI)
	{
		*step_dir_x = -1;
		*step_dir_y = -1;
	}
	if (rad >= M_PI && rad <= 1.5 * M_PI)
	{
		*step_dir_x = -1;
		*step_dir_y = 1;
	}
	if (rad >= 1.5 * M_PI && rad <= 2 * M_PI)
	{
		*step_dir_x = 1;
		*step_dir_y = 1;
	}
}

char	wall_face(int is_wall, t_dda *dda)
{
	if (is_wall == 1)
		is_wall *= dda->step_direction_x;
	if (is_wall == 2)
		is_wall *= dda->step_direction_y;
	if (is_wall == 1)
		return ('O');
	if (is_wall == -1)
		return ('W');
	if (is_wall == 2)
		return ('S');
	if (is_wall == -2)
		return ('N');
	return (0);
}

void	init_dda(t_dda *dda, t_data *data, double angle)
{
	dda->delta_x = 0;
	dda->delta_y = 0;
	dda->angle = angle;
	dda->len = 0;
	dda->start_x = data->player.pos.x / 64;
	dda->start_y = data->player.pos.y / 64;
	dda->end_x = dda->start_x;
	dda->end_y = dda->start_y;
	dda->texture = 0;
	dda->door_end_x = 0;
	dda->door_end_y = 0;
	get_dir(dda->angle, &dda->step_direction_x, &dda->step_direction_y);
}

void	dda_algo(t_dda *dda, t_data *data, double angle)
{
	int	is_wall;

	is_wall = 0;
	init_dda(dda, data, angle);
	dda->end_x = dda->start_x;
	dda->end_y = dda->start_y;
	while (1)
	{
		is_wall = get_new_pos(dda, data->map->map);
		if (is_wall > 0)
			break ;
	}
	dda->wall_face = wall_face(is_wall, dda);
	dda->delta_x = dda->end_x - dda->start_x;
	dda->delta_y = dda->end_y - dda->start_y;
	dda->len = pow(pow(dda->delta_x, 2) + pow(dda->delta_y, 2), 0.5);
}
