/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:08:59 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/07 11:22:04 by niklasburch      ###   ########.fr       */
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

static bool	wall_collision(t_data *data)
{
	// float		x;
	// float		y;

	// x = data->player.pos.x + cos(data->player.dir) * MOVE_SPEED;
	// y = data->player.pos.y - sin(data->player.dir) * MOVE_SPEED;
	// if (data->map->map[(int)y][(int)x] == '1')
	// 	return (true);
	// return (false);
	(void)data;
	return (false);
}

void	movement(t_data *data)
{
	if (data->keys[MLX_KEY_W] && !wall_collision(data))
	{
		data->player.pos.x += cos(data->player.dir) * MOVE_SPEED;
		data->player.pos.y -= sin(data->player.dir) * MOVE_SPEED;
	}
	if (data->keys[MLX_KEY_S])
	{
		data->player.pos.x -= cos(data->player.dir) * MOVE_SPEED;
		data->player.pos.y += sin(data->player.dir) * MOVE_SPEED;
	}
	if (data->keys[MLX_KEY_A])
	{
		data->player.pos.x -= sin(data->player.dir) * MOVE_SPEED;
		data->player.pos.y -= cos(data->player.dir) * MOVE_SPEED;
	}
	if (data->keys[MLX_KEY_D])
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