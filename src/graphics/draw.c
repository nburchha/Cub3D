/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 20:17:01 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/19 20:48:43 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_circle(float coords[2], float radius, uint32_t color,
		mlx_image_t *img)
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
			dist = sqrtf((i - radius) * (i - radius) + (j - radius) * (j
						- radius));
			if (dist < radius)
				mlx_put_pixel(img, coords[0] + i - radius, coords[1] + j
					- radius, color);
		}
	}
}

void	draw_line(t_coordinates start, t_coordinates end, uint32_t color,
		mlx_image_t *img)
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
		mlx_put_pixel(img, x, y, color);
		x += dx;
		y += dy;
	}
}

void	draw_triangle(t_data *data, float direction, uint32_t color)
{
	t_coordinates	center;
	float	radius;
	t_coordinates coords[3];

	center.x = M_SCALE * 5 + M_SCALE / 2;
	center.y = M_SCALE * 5 + M_SCALE / 2;
	radius = M_SCALE / 2;
	direction = normalize_angle(-direction);
	center.x += M_SCALE / 2 * cos(direction);
	center.y += M_SCALE / 2 * sin(direction);
	coords[0].x = center.x + radius * cos(direction);
	coords[0].y = center.y + radius * sin(direction);
	coords[1].x = center.x + radius * cos(direction + 2 * M_PI / 3);
	coords[1].y = center.y + radius * sin(direction + 2 * M_PI / 3);
	coords[2].x = center.x + radius * cos(direction - 2 * M_PI / 3);
	coords[2].y = center.y + radius * sin(direction - 2 * M_PI / 3);
	draw_line((t_coordinates){coords[0].x, coords[0].y}, (t_coordinates){coords[1].x, coords[1].y}, color, data->minimap);
	draw_line((t_coordinates){coords[0].x, coords[0].y}, (t_coordinates){coords[2].x, coords[2].y}, color, data->minimap);
	draw_line((t_coordinates){coords[1].x, coords[1].y}, (t_coordinates){coords[2].x, coords[2].y}, color, data->minimap);
}
