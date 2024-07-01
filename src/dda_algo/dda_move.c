/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:12:59 by psanger           #+#    #+#             */
/*   Updated: 2024/07/01 17:27:30 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	move_x(t_dda *dda, char **map, double hyplen_x)
{
	dda->end_x = dda->end_x + dda->delta_x;
	dda->end_y = dda->end_y + (hyplen_x * fabs(sin(dda->angle))
			* dda->step_direction_y);
	if (is_wall_x(map, dda) == 1)
		return (1);
	return (0);
}

int	move_y(t_dda *dda, char **map, double hyplen_y)
{
	dda->end_y = dda->end_y + dda->delta_y;
	dda->end_x = dda->end_x + (hyplen_y * fabs(cos(dda->angle))
			* dda->step_direction_x);
	if (is_wall_y(map, dda) == 1)
		return (2);
	return (0);
}

int	get_new_pos(t_dda *dda, char **map)
{
	double	hyplen_x;
	double	hyplen_y;

	hyplen_x = 0;
	hyplen_y = 0;
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
	hyplen_x = fabs(dda->delta_x) / fabs(cos(dda->angle));
	hyplen_y = fabs(dda->delta_y) / fabs(sin(dda->angle));
	if (hyplen_x < hyplen_y)
		return (move_x(dda, map, hyplen_x));
	else
		return (move_y(dda, map, hyplen_y));
	return (0);
}
