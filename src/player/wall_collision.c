/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:21:59 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/19 16:32:46 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_coordinates	calculate_new_position(t_data *data,
		const char direction)
{
	t_coordinates	pos;

	if (direction == 'W')
		pos = (t_coordinates){data->player.pos.x + cos(data->player.dir) \
			* MOVE_SPEED, data->player.pos.y - sin(data->player.dir) \
			* MOVE_SPEED};
	else if (direction == 'S')
		pos = (t_coordinates){data->player.pos.x - cos(data->player.dir) \
			* MOVE_SPEED, data->player.pos.y + sin(data->player.dir) \
			* MOVE_SPEED};
	else if (direction == 'A')
		pos = (t_coordinates){data->player.pos.x - sin(data->player.dir) \
			* MOVE_SPEED, data->player.pos.y - cos(data->player.dir) \
			* MOVE_SPEED};
	else
		pos = (t_coordinates){data->player.pos.x + sin(data->player.dir) \
			* MOVE_SPEED, data->player.pos.y + cos(data->player.dir) \
			* MOVE_SPEED};
	return (pos);
}

static bool	check_collision(t_data *data, t_coordinates pos, float player_size,
		const char xy)
{
	if (xy == 'x')
	{
		if (ft_strchr("12", data->map->map[(int)(data->player.pos.y / \
			PIXEL_SIZE)][(int)((pos.x - player_size) / PIXEL_SIZE)])
			|| ft_strchr("12", data->map->map[(int)(data->player.pos.y
			/ PIXEL_SIZE)][(int)((pos.x + player_size)
			/ PIXEL_SIZE)]))
			return (true);
	}
	else if (xy == 'y')
	{
		if (ft_strchr("12", data->map->map[(int)((pos.y - player_size) / \
			PIXEL_SIZE)][(int)(data->player.pos.x / PIXEL_SIZE)]) || \
			ft_strchr("12", data->map->map[(int)((pos.y + player_size) / \
			PIXEL_SIZE)][(int)(data->player.pos.x / PIXEL_SIZE)]))
			return (true);
	}
	return (false);
}

bool	wall_collision(t_data *data, const char direction, const char xy)
{
	t_coordinates	pos;
	float			player_size;

	player_size = PIXEL_SIZE / 8;
	pos = calculate_new_position(data, direction);
	return (check_collision(data, pos, player_size, xy));
}
