/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:23:37 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/19 17:58:46 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_circle(float coords[2], float radius, uint32_t color, mlx_image_t *img)
{
	float	dist;
	int		i;
	int		j;

	i = -1;
	while (++i < PIXEL_SIZE)
	{
		j = -1;
		while (++j < PIXEL_SIZE)
		{
			dist = sqrtf((i - radius) * (i - radius) + (j - radius) * \
						(j - radius));
			if (dist < radius)
				mlx_put_pixel(img, coords[0] + i - radius, coords[1] + \
								j - radius, color);
		}
	}
}

void	draw_line(t_coordinates start, t_coordinates end, uint32_t color, \
				t_data *data)
{
	float	dx;
	float	dy;
	float	step;
	float	x;
	float	y;

	dx = end.x - start.x;
	dy = end.y - start.y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx /= step;
	dy /= step;
	x = start.x;
	y = start.y;
	while ((int)(x - end.x) || (int)(y - end.y))
	{
		mlx_put_pixel(data->image, x, y, color);
		x += dx;
		y += dy;
	}
}

void	render_player(t_data *data)
{
	draw_circle((float [2]){data->player.pos.x, data->player.pos.y}, PIXEL_SIZE / \
				8, 0xFF0000FF, data->image);
	float ray_angle = data->player.dir - (FOV / 2) * (M_PI / 180);
	while (ray_angle <= data->player.dir + ((FOV / 2) * (M_PI / 180)))
	{
		dda_algo(data, normalize_angle(ray_angle));
		ray_angle += ((FOV / 2) * (M_PI / 180)) / WIDTH;
	}
}
