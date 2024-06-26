/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 09:25:20 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/26 16:16:00 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cursor_hook(double xpos, double ypos, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->player.dir -= ((xpos - WIDTH / 2) * ROTATE_SPEED) * (M_PI / 180);
	data->player.dir = normalize_angle(data->player.dir);
	mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
	(void)ypos;
}
