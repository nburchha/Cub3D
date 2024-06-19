/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:40:27 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/20 01:38:03 by psanger          ###   ########.fr       */
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

static void	door_in_reach(t_data *data)
{
	t_dda	dda;
	float	open_door_len;
	int		x;
	int		y;

	dda_algo(&dda, data, data->player.dir);
	if (data->map->map[(int)(data->player.pos.y / 64)][(int)(data->player.pos.x
			/ 64)] == 2 || data->map->map[(int)(data->player.pos.y
			/ 64)][(int)(data->player.pos.x / 64)] == 3)
		return ;
	x = dda.door_end_x;
	y = dda.door_end_y;
	open_door_len = pow(pow(dda.door_end_x - dda.start_x, 2)
			+ pow(dda.door_end_y - dda.start_y, 2), 0.5);
	if (dda.is_open_door == 2)
	{
		if (data->map->map[y][x] == '2' && open_door_len < (float)3)
			data->map->map[y][x] = '3';
	}
	if (dda.is_open_door == 3)
	{
		if (data->map->map[y][x] == '3' && open_door_len < (float)3)
			data->map->map[y][x] = '2';
	}
}

static void	movement_wasd(t_data *data)
{
	int	speed;

	speed = MOVE_SPEED;
	if (data->keys[MLX_KEY_LEFT_SHIFT])
		speed *= 2;
	if (data->keys[MLX_KEY_F])
		door_in_reach(data);
	if (data->keys[MLX_KEY_W] && !wall_collision(data, 'W', 'x'))
		data->player.pos.x += cos(data->player.dir) * speed;
	if (data->keys[MLX_KEY_W] && !wall_collision(data, 'W', 'y'))
		data->player.pos.y -= sin(data->player.dir) * speed;
	if (data->keys[MLX_KEY_S] && !wall_collision(data, 'S', 'x'))
		data->player.pos.x -= cos(data->player.dir) * speed;
	if (data->keys[MLX_KEY_S] && !wall_collision(data, 'S', 'y'))
		data->player.pos.y += sin(data->player.dir) * speed;
	if (data->keys[MLX_KEY_A] && !wall_collision(data, 'A', 'x'))
		data->player.pos.x += sin(data->player.dir) * speed;
	if (data->keys[MLX_KEY_A] && !wall_collision(data, 'A', 'y'))
		data->player.pos.y += cos(data->player.dir) * speed;
	if (data->keys[MLX_KEY_D] && !wall_collision(data, 'D', 'x'))
		data->player.pos.x -= sin(data->player.dir) * speed;
	if (data->keys[MLX_KEY_D] && !wall_collision(data, 'D', 'y'))
		data->player.pos.y -= cos(data->player.dir) * speed;
}

void	movement(t_data *data)
{
	movement_wasd(data);
	if (BONUS)
		mouse_movement(data);
	if (data->keys[MLX_KEY_LEFT])
		data->player.dir -= ROTATE_SPEED;
	if (data->keys[MLX_KEY_RIGHT])
		data->player.dir += ROTATE_SPEED;
	data->player.dir = normalize_angle(data->player.dir);
}
