/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:00:10 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/07 09:12:56 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

#include "../../inc/cub3d.h"

void	movement(t_data *data)
{
	if (data->keys[MLX_KEY_W])
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
		data->player.dir -= 0.1f;
	if (data->keys[MLX_KEY_RIGHT])
		data->player.dir += 0.1f;
}

void keyhook(mlx_key_data_t keydata, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	else if (keydata.key <= MAX_KEY && keydata.action == MLX_PRESS)
		data->keys[keydata.key] = true;
	else if (keydata.key <= MAX_KEY && keydata.action == MLX_RELEASE)
		data->keys[keydata.key] = false;
	movement(data);
	render_map(data);
	render_player(data);
}