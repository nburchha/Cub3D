/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:23:37 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/07 11:07:51 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_circle(float x, float y, uint32_t color, t_data *data)
{
	float	radius;
	float	dist;
	int		i;
	int		j;

	radius = PIXEL_SIZE / 4;
	i = -1;
	while (++i < PIXEL_SIZE)
	{
		j = -1;
		while (++j < PIXEL_SIZE)
		{
			dist = sqrtf((i - radius) * (i - radius) + (j - radius) * (j - radius));
			if (dist < radius)
				mlx_put_pixel(data->image, x * PIXEL_SIZE + i + radius, y * PIXEL_SIZE + j + radius, color);
		}
	}
}

void draw_line(t_coordinates start, t_coordinates end, uint32_t color, t_data *data)
{
	float	dx;
	float	dy;
	float	step;
	float	x;
	float	y;

	dx = end.x - start.x;
	dy = end.y - start.y;
	// step = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
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
	t_coordinates start;
	t_coordinates end;

	// printf("player pos x: %f\n", data->player.pos.x);
	// printf("player dir: %f\n", data->player.dir);
	draw_circle(data->player.pos.x, data->player.pos.y, 0xFF0000FF, data);
	start = (t_coordinates){data->player.pos.x * PIXEL_SIZE + PIXEL_SIZE / 2, data->player.pos.y * PIXEL_SIZE + PIXEL_SIZE / 2};
	end = (t_coordinates){start.x + cos(data->player.dir) * PIXEL_SIZE, start.y - sin(data->player.dir) * PIXEL_SIZE};
	draw_line(start, end, 0xFF0000FF, data);
}