/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:23:37 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/17 21:19:55 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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

float	to_rad(int angle)
{
	return (M_PI / 180 * angle);
}

void cast(t_data *data, t_dda *dda, int column)
{
	float real_len = fabs(cos((to_rad((FOV * (-1)) / 2) + ((FOV / WIDTH) * column))) * dda->len);
	float height = (800 / real_len) / 2;

	if (height > HEIGHT / 2)
		height = HEIGHT / 2;

	int	color;
	if (dda->wall_face == 'N')
		color = 0xFF7F24FF;
	if (dda->wall_face == 'O')
		color = 0x97FFFFFF;
	if (dda->wall_face == 'S')
		color = 0x228B22FF;
	if (dda->wall_face == 'W')
		color = 0xFF1493FF;

	int mid = HEIGHT / 2;
	for (int i = mid; i < mid + height; i++) {
		if (i < HEIGHT)
			mlx_put_pixel(data->image, column, i, color);
	}
	for (int i = mid - height; i < mid; i++) {
		if (i > 0)
			mlx_put_pixel(data->image, column, i, color);
	}
}

void	render_player(t_data *data)
{
	draw_circle(data->player.pos.x, data->player.pos.y, 0xFF0000FF, data);
	float ray_angle = data->player.dir - (FOV / 2) * (M_PI / 180);
	int column = 0;
	reset_canvas(data);
	t_dda	dda;
	while (ray_angle <= data->player.dir + ((FOV / 2) * (M_PI / 180)))
	{
		dda_algo(&dda, data, normalize_angle(ray_angle));
		cast(data, &dda, column);
		ray_angle += (FOV) * (M_PI / 180) / WIDTH;
		column++;
	}
}
