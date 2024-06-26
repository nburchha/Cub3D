/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:40:27 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/26 22:59:29 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	movement_wasd(t_data *data)
{
	int	speed;

	speed = MOVE_SPEED;
	if (data->keys[MLX_KEY_LEFT_SHIFT])
		speed *= 2;
	if (data->keys[MLX_KEY_W] && !wall_collision(data, 'W', 'x'))
		data->player.pos.x += cos(data->player.dir) * speed;
	if (data->keys[MLX_KEY_W] && !wall_collision(data, 'W', 'y'))
		data->player.pos.y -= sin(data->player.dir) * speed;
	if (data->keys[MLX_KEY_S] && !wall_collision(data, 'S', 'x'))
		data->player.pos.x -= cos(data->player.dir) * speed;
	if (data->keys[MLX_KEY_S] && !wall_collision(data, 'S', 'y'))
		data->player.pos.y += sin(data->player.dir) * speed;
	if (data->keys[MLX_KEY_D] && !wall_collision(data, 'D', 'x'))
		data->player.pos.x += sin(data->player.dir) * speed;
	if (data->keys[MLX_KEY_D] && !wall_collision(data, 'D', 'y'))
		data->player.pos.y += cos(data->player.dir) * speed;
	if (data->keys[MLX_KEY_A] && !wall_collision(data, 'A', 'x'))
		data->player.pos.x -= sin(data->player.dir) * speed;
	if (data->keys[MLX_KEY_A] && !wall_collision(data, 'A', 'y'))
		data->player.pos.y -= cos(data->player.dir) * speed;
}

void	movement(t_data *data)
{
	movement_wasd(data);
	if (data->keys[MLX_KEY_RIGHT])
		data->player.dir -= ROTATE_SPEED;
	if (data->keys[MLX_KEY_LEFT])
		data->player.dir += ROTATE_SPEED;
	data->player.dir = normalize_angle(data->player.dir);
}
