/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:08:59 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/07 15:26:03 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	normalize_angle(float *angle)
{
	if (*angle < 0)
		*angle += 2 * M_PI;
	if (*angle > 2 * M_PI)
		*angle -= 2 * M_PI;
}

static bool	wall_collision(t_data *data, const char direction)
{
	t_coordinates	pos;
	float			half_size = PIXEL_SIZE / 8; //player cant move closer to a wall

	if (direction == 'W')
	{
		pos.x = data->player.pos.x + cos(data->player.dir) * MOVE_SPEED;
		pos.y = data->player.pos.y - sin(data->player.dir) * MOVE_SPEED;
	}
	else if (direction == 'S')
	{
		pos.x = data->player.pos.x - cos(data->player.dir) * MOVE_SPEED;
		pos.y = data->player.pos.y + sin(data->player.dir) * MOVE_SPEED;
	}
	else if (direction == 'A')
	{
		pos.x = data->player.pos.x - sin(data->player.dir) * MOVE_SPEED;
		pos.y = data->player.pos.y - cos(data->player.dir) * MOVE_SPEED;
	}
	else
	{
		pos.x = data->player.pos.x + sin(data->player.dir) * MOVE_SPEED;
		pos.y = data->player.pos.y + cos(data->player.dir) * MOVE_SPEED;
	}

	// Check collision for each corner of the player's bounding box
	if (data->map->map[(int)((pos.y - half_size) / PIXEL_SIZE)][(int)((pos.x - half_size) / PIXEL_SIZE)] == '1' ||
		data->map->map[(int)((pos.y - half_size) / PIXEL_SIZE)][(int)((pos.x + half_size) / PIXEL_SIZE)] == '1' ||
		data->map->map[(int)((pos.y + half_size) / PIXEL_SIZE)][(int)((pos.x - half_size) / PIXEL_SIZE)] == '1' ||
		data->map->map[(int)((pos.y + half_size) / PIXEL_SIZE)][(int)((pos.x + half_size) / PIXEL_SIZE)] == '1')
	{
		return (true);
	}

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
	normalize_angle(&data->player.dir);
}

void	general_hook(void *param)
{
	t_data *data;

	data = (t_data *)param;
	movement(data);
	render_map(data);
	render_player(data);
}