/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:00:15 by psanger           #+#    #+#             */
/*   Updated: 2024/06/26 17:08:55 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	door_is_closed(t_dda *dda, int x_pos_int, int y_pos_int)
{
	dda->is_open_door = 2;
	dda->door_end_x = x_pos_int;
	dda->door_end_y = y_pos_int;
}

void	door_is_open(t_dda *dda, int x_pos_int, int y_pos_int)
{
	dda->is_open_door = 3;
	dda->door_end_x = x_pos_int;
	dda->door_end_y = y_pos_int;
}

int	is_wall_x(char **map, t_dda *dda)
{
	int	x_pos_int;
	int	y_pos_int;

	x_pos_int = (int)dda->end_x;
	y_pos_int = (int)dda->end_y;
	if (dda->step_direction_x == -1)
		x_pos_int += -1;
	if (map[y_pos_int][x_pos_int] == '2' && dda->door_end_x == 0
		&& dda->door_end_y == 0)
		door_is_closed(dda, x_pos_int, y_pos_int);
	if (map[y_pos_int][x_pos_int] == '3' && dda->door_end_x == 0
		&& dda->door_end_y == 0)
		door_is_open(dda, x_pos_int, y_pos_int);
	if (map[y_pos_int][x_pos_int] == '1' || map[y_pos_int][x_pos_int] == '2')
	{
		if (map[y_pos_int][x_pos_int] == '2')
			dda->texture = 2;
		else
			dda->texture = 1;
		return (1);
	}
	return (0);
}

int	is_wall_y(char **map, t_dda *dda)
{
	int	x_pos_int;
	int	y_pos_int;

	x_pos_int = (int)dda->end_x;
	y_pos_int = (int)dda->end_y;
	if (dda->step_direction_y == -1)
		y_pos_int += -1;
	if (map[y_pos_int][x_pos_int] == '2' && dda->door_end_x == 0
		&& dda->door_end_y == 0)
		door_is_closed(dda, x_pos_int, y_pos_int);
	if (map[y_pos_int][x_pos_int] == '3' && dda->door_end_x == 0
		&& dda->door_end_y == 0)
		door_is_open(dda, x_pos_int, y_pos_int);
	if (map[y_pos_int][x_pos_int] == '1' || map[y_pos_int][x_pos_int] == '2')
	{
		if (map[y_pos_int][x_pos_int] == '2')
			dda->texture = 2;
		else
			dda->texture = 1;
		return (1);
	}
	return (0);
}
