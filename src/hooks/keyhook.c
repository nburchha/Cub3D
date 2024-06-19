/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:00:10 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/17 20:10:18 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(data->mlx);
	else if (keydata.key <= MAX_KEY && keydata.action == MLX_PRESS)
		data->keys[keydata.key] = true;
	else if (keydata.key <= MAX_KEY && keydata.action == MLX_RELEASE)
		data->keys[keydata.key] = false;
}
