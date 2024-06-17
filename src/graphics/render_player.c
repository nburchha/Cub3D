/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:23:37 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/17 20:25:45 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_circle(float x, float y, uint32_t color, t_data *data)
{
	float	radius;
	float	dist;
	int		i;
	int		j;

	radius = PIXEL_SIZE / 8;
	i = -1;
	while (++i < PIXEL_SIZE)
	{
		j = -1;
		while (++j < PIXEL_SIZE)
		{
			dist = sqrtf((i - radius) * (i - radius) + (j - radius) * \
						(j - radius));
			if (dist < radius)
				mlx_put_pixel(data->image, x + i - radius, y + \
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
	// t_coordinates	start;
	// t_coordinates	end;

	draw_circle(data->player.pos.x, data->player.pos.y, 0xFF0000FF, data);
	float ray_angle = data->player.dir - (FOV / 2) * (M_PI / 180);
	while (ray_angle <= data->player.dir + ((FOV / 2) * (M_PI / 180)))
	{
		dda_algo(data, normalize_angle(ray_angle));
		ray_angle += ((FOV / 2) * (M_PI / 180)) / WIDTH;
	}


}
