/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_canvas.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:08:05 by psanger           #+#    #+#             */
/*   Updated: 2024/06/22 19:54:45 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	reset_canvas(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y <= HEIGHT / 2)
	{
		while (x <= WIDTH - 1)
		{
			mlx_put_pixel(data->image, x, y, data->ceiling_color);
			x++;
		}
		x = 0;
		y++;
	}
	while (y <= HEIGHT - 1)
	{
		while (x <= WIDTH - 1)
		{
			mlx_put_pixel(data->image, x, y, data->floor_color);
			x++;
		}
		x = 0;
		y++;
	}
}

