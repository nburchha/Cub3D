/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:40:27 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/17 20:25:45 by niklasburch      ###   ########.fr       */
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
		if (data->map->map[(int)(data->player.pos.y / PIXEL_SIZE)][(int)((pos.x
					- player_size) / PIXEL_SIZE)] == '1'
			|| data->map->map[(int)(data->player.pos.y
				/ PIXEL_SIZE)][(int)((pos.x + player_size)
				/ PIXEL_SIZE)] == '1')
			return (true);
	}
	else if (xy == 'y')
	{
		if (data->map->map[(int)((pos.y - player_size)
				/ PIXEL_SIZE)][(int)(data->player.pos.x / PIXEL_SIZE)] == '1'
			|| data->map->map[(int)((pos.y + player_size)
				/ PIXEL_SIZE)][(int)(data->player.pos.x / PIXEL_SIZE)] == '1')
			return (true);
	}
	return (false);
}

static bool	wall_collision(t_data *data, const char direction, const char xy)
{
	t_coordinates	pos;
	float			player_size;

	player_size = PIXEL_SIZE / 8;
	pos = calculate_new_position(data, direction);
	return (check_collision(data, pos, player_size, xy));
}

static void	movement_wasd(t_data *data)
{
	if (data->keys[MLX_KEY_W] && !wall_collision(data, 'W', 'x'))
		data->player.pos.x += cos(data->player.dir) * MOVE_SPEED;
	if (data->keys[MLX_KEY_W] && !wall_collision(data, 'W', 'y'))
		data->player.pos.y -= sin(data->player.dir) * MOVE_SPEED;
	if (data->keys[MLX_KEY_S] && !wall_collision(data, 'S', 'x'))
		data->player.pos.x -= cos(data->player.dir) * MOVE_SPEED;
	if (data->keys[MLX_KEY_S] && !wall_collision(data, 'S', 'y'))
		data->player.pos.y += sin(data->player.dir) * MOVE_SPEED;
	if (data->keys[MLX_KEY_A] && !wall_collision(data, 'A', 'x'))
		data->player.pos.x -= sin(data->player.dir) * MOVE_SPEED;
	if (data->keys[MLX_KEY_A] && !wall_collision(data, 'A', 'y'))
		data->player.pos.y -= cos(data->player.dir) * MOVE_SPEED;
	if (data->keys[MLX_KEY_D] && !wall_collision(data, 'D', 'x'))
		data->player.pos.x += sin(data->player.dir) * MOVE_SPEED;
	if (data->keys[MLX_KEY_D] && !wall_collision(data, 'D', 'y'))
		data->player.pos.y += cos(data->player.dir) * MOVE_SPEED;
}

void	movement(t_data *data)
{
	movement_wasd(data);
	if (data->keys[MLX_KEY_LEFT])
		data->player.dir += ROTATE_SPEED;
	if (data->keys[MLX_KEY_RIGHT])
		data->player.dir -= ROTATE_SPEED;
	data->player.dir = normalize_angle(data->player.dir);
}
