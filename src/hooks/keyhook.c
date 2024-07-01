/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:00:10 by niklasburch       #+#    #+#             */
/*   Updated: 2024/07/01 17:27:30 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	door_in_reach(t_data *data)
{
	t_dda	dda;
	double	open_door_len;
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
		if (data->map->map[y][x] == DOOR && open_door_len < (double)3)
			data->map->map[y][x] = OPEN_DOOR;
	}
	if (dda.is_open_door == 3)
	{
		if (data->map->map[y][x] == OPEN_DOOR && open_door_len < (double)3)
			data->map->map[y][x] = DOOR;
	}
}

void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	else if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
		door_in_reach(data);
	else if (keydata.key <= MAX_KEY && keydata.action == MLX_PRESS)
		data->keys[keydata.key] = true;
	else if (keydata.key <= MAX_KEY && keydata.action == MLX_RELEASE)
		data->keys[keydata.key] = false;
}
