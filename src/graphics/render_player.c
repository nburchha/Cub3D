/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:23:37 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/26 17:48:31 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	to_rad(int angle)
{
	return (M_PI / 180 * angle);
}

static void	draw_crosshair(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (i <= 1)
	{
		j = 0;
		while (j < 10)
		{
			mlx_put_pixel(data->image, WIDTH / 2 + i, HEIGHT / 2 + j,
				0x000000FF);
			mlx_put_pixel(data->image, WIDTH / 2 + i, HEIGHT / 2 - j,
				0x000000FF);
			mlx_put_pixel(data->image, WIDTH / 2 + j, HEIGHT / 2 + i,
				0x000000FF);
			mlx_put_pixel(data->image, WIDTH / 2 - j, HEIGHT / 2 + i,
				0x000000FF);
			j++;
		}
		i++;
	}
}

void	render_player(t_data *data)
{
	float	ray_angle;
	int		column;
	t_dda	dda;

	ray_angle = data->player.dir - (FOV / 2) * (M_PI / 180);
	column = WIDTH;
	reset_canvas(data);
	while (ray_angle <= data->player.dir + ((FOV / 2) * (M_PI / 180)))
	{
		dda_algo(&dda, data, normalize_angle(ray_angle));
		cast_projection(data, &dda, column);
		ray_angle += (FOV) * (M_PI / 180) / WIDTH;
		column--;
	}
	draw_crosshair(data);
}
