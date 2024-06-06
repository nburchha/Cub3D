/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:00:10 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/06 10:57:35 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void keyhook(mlx_key_data_t keydata, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	else if (keydata.key == MLX_KEY_W)
		data->player.pos.y -= (4 / data->scale);
	else if (keydata.key == MLX_KEY_S)
		data->player.pos.y += (4 / data->scale);
	else if (keydata.key == MLX_KEY_A)
		data->player.pos.x -= (4 / data->scale);
	else if (keydata.key == MLX_KEY_D)
		data->player.pos.x += (4 / data->scale);
	render_map(data);
	render_player(data);
}