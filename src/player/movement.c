/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:40:27 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/17 18:40:29 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	wall_collision(t_data *data, const char direction)
{
	t_coordinates	pos;
	float			player_size;

	player_size = PIXEL_SIZE / 8; //player cant move closer to a wall
	if (direction == 'W')
		pos = (t_coordinates){data->player.pos.x + cos(data->player.dir) * \
		MOVE_SPEED, data->player.pos.y - sin(data->player.dir) * MOVE_SPEED};
	else if (direction == 'S')
		pos = (t_coordinates){data->player.pos.x - cos(data->player.dir) * \
		MOVE_SPEED, data->player.pos.y + sin(data->player.dir) * MOVE_SPEED};
	else if (direction == 'A')
		pos = (t_coordinates){data->player.pos.x - sin(data->player.dir) * \
		MOVE_SPEED, data->player.pos.y - cos(data->player.dir) * MOVE_SPEED};
	else
		pos = (t_coordinates){data->player.pos.x + sin(data->player.dir) * \
		MOVE_SPEED, data->player.pos.y + cos(data->player.dir) * MOVE_SPEED};
	if (data->map->map[(int)((pos.y - player_size) / PIXEL_SIZE)][(int)((pos.x \
	- player_size) / PIXEL_SIZE)] == '1' || data->map->map[(int)((pos.y - \
	player_size) / PIXEL_SIZE)][(int)((pos.x + player_size) / PIXEL_SIZE)] == \
	'1' || data->map->map[(int)((pos.y + player_size) / PIXEL_SIZE)][(int) \
	((pos.x - player_size) / PIXEL_SIZE)] == '1' || data->map->map[(int) \
	((pos.y + player_size) / PIXEL_SIZE)][(int)((pos.x + player_size) / \
	PIXEL_SIZE)] == '1')
		return (true);
	return (false);
}

void	movement(t_data *data)
{
	if (data->keys[MLX_KEY_W] && !wall_collision(data, 'W'))
	{
		data->player.pos.x += cos(data->player.dir) * MOVE_SPEED;
		data->player.pos.y -= sin(data->player.dir) * MOVE_SPEED;
	}
	if (data->keys[MLX_KEY_S] && !wall_collision(data, 'S'))
	{
		data->player.pos.x -= cos(data->player.dir) * MOVE_SPEED;
		data->player.pos.y += sin(data->player.dir) * MOVE_SPEED;
	}
	if (data->keys[MLX_KEY_A] && !wall_collision(data, 'A'))
	{
		data->player.pos.x -= sin(data->player.dir) * MOVE_SPEED;
		data->player.pos.y -= cos(data->player.dir) * MOVE_SPEED;
	}
	if (data->keys[MLX_KEY_D] && !wall_collision(data, 'D'))
	{
		data->player.pos.x += sin(data->player.dir) * MOVE_SPEED;
		data->player.pos.y += cos(data->player.dir) * MOVE_SPEED;
	}
	if (data->keys[MLX_KEY_LEFT])
		data->player.dir += ROTATE_SPEED;
	if (data->keys[MLX_KEY_RIGHT])
		data->player.dir -= ROTATE_SPEED;
	data->player.dir = normalize_angle(data->player.dir);
}
