/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 16:07:05 by psanger           #+#    #+#             */
/*   Updated: 2024/06/17 20:25:45 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	to_angle(int angle)
{
	return (angle * (180 / M_PI));
}

void	get_dir(float rad, int *step_dir_x, int *step_dir_y)
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

int	is_wall_x(char **map, t_dda *dda)
{
	int		x_pos_int = (int)dda->end_x;
	int		y_pos_int = (int)dda->end_y;
	if (dda->step_direction_x == -1)
		x_pos_int += -1;
	if (map[y_pos_int][x_pos_int] == '1')
		return (1);
	return (0);
}

int	is_wall_y(char **map, t_dda *dda)
{
	int		x_pos_int = (int)dda->end_x;
	int		y_pos_int = (int)dda->end_y;
	if (dda->step_direction_y == -1)
		y_pos_int += -1;
	if (map[y_pos_int][x_pos_int] == '1')
		return (1);
	return (0);
}

float	abs_float(float num)
{
	if (num < 0)
		num = num * -1;
	return (num);
}

char	wall_face(int is_wall, t_dda *dda)
{
	if (is_wall == 1)
		is_wall *= dda->step_direction_x;
	if (is_wall == 2)
		is_wall *= dda->step_direction_y;
	if (is_wall == 1)
		return ('W');
	if (is_wall == -1)
		return ('O');
	if (is_wall == 2)
		return ('N');
	if (is_wall == -2)
		return ('S');
	return (0);
}

int	get_new_pos(t_dda *dda, char **map)
{
	float	hyplen_x = 0;
	float	hyplen_y = 0;

	if (dda->step_direction_x > 0)
		dda->delta_x = (int)dda->end_x + 1 - dda->end_x;
	else
		dda->delta_x = (int)dda->end_x - dda->end_x;
	if (dda->step_direction_y > 0)
		dda->delta_y = (int)dda->end_y + 1 - dda->end_y;
	else
		dda->delta_y = (int)dda->end_y - dda->end_y;

	if (dda->delta_x == 0)
		dda->delta_x = dda->step_direction_x;
	if (dda->delta_y == 0)
		dda->delta_y = dda->step_direction_y;



	hyplen_x = abs_float(dda->delta_x) / abs_float(cos(dda->angle));
	hyplen_y = abs_float(dda->delta_y) / abs_float(sin(dda->angle));

	if (hyplen_x < hyplen_y)
	{
		dda->end_x = dda->end_x + dda->delta_x;
		dda->end_y = dda->end_y + (hyplen_x * abs_float(sin(dda->angle)) * dda->step_direction_y);
		if (is_wall_x(map, dda) == 1)
			return (1);
	}
	else
	{
		dda->end_x = dda->end_x + (hyplen_y * abs_float(cos(dda->angle)) * dda->step_direction_x);
		dda->end_y = dda->end_y + dda->delta_y;
		if (is_wall_y(map, dda) == 1)
			return (2);
	}
	return (0);
}

void	init_dda(t_dda *dda, t_data *data, float angle)
{
	dda->delta_x = 0;
	dda->delta_y = 0;
	dda->angle = angle;
	dda->len = 0;
	dda->start_x = data->player.pos.x / 64;
	dda->start_y = data->player.pos.y / 64;
	dda->end_x = dda->start_x;
	dda->end_y = dda->start_y;
	get_dir(dda->angle, &dda->step_direction_x, &dda->step_direction_y);
}

void	dda_algo(t_data *data, float angle)
{
	int	is_wall = 0;
	t_dda dda;
	init_dda(&dda, data, angle);
	dda.end_x = dda.start_x;
	dda.end_y = dda.start_y;
	while (1)
	{
		is_wall = get_new_pos(&dda, data->map->map);
		if (is_wall > 0)
			break;
	}
	dda.wall_face = wall_face(is_wall, &dda);
	dda.delta_x = dda.end_x - dda.start_x;
	dda.delta_y = dda.end_y - dda.start_y;
	// printf("start |%f|, |%f|\n", dda.start_x, dda.start_y);
	// printf("end |%f|, |%f|\n", dda.end_x, dda.end_y);
	dda.len = pow(pow(dda.delta_x, 2) + pow(dda.delta_y, 2), 0.5);

	draw_line(data->player.pos, (t_coordinates){dda.end_x * 64, dda.end_y * 64}, 0x0000000FF, data);
	printf("len : |%f|\n", dda.len);
}




