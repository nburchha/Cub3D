/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:40:27 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/20 19:08:23 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	mouse_movement(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	mlx_get_mouse_pos(data->mlx, &x, &y);
	data->player.dir += ((x - WIDTH / 2) * ROTATE_SPEED) * (M_PI / 180);
	data->player.dir = normalize_angle(data->player.dir);
	mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
}

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
	if (BONUS)
		mouse_movement(data);
	if (data->keys[MLX_KEY_RIGHT])
		data->player.dir -= ROTATE_SPEED;
	if (data->keys[MLX_KEY_LEFT])
		data->player.dir += ROTATE_SPEED;
	data->player.dir = normalize_angle(data->player.dir);
}
