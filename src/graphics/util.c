/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:48:48 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/22 15:52:14 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	normalize_angle(float angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

bool	valid_coords(t_data *data, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->map->width || y >= data->map->height)
		return (false);
	return (true);
}

void	reset_image(mlx_image_t *image, int color)
{
	uint32_t	x;
	uint32_t	y;

	y = -1;
	while (++y < image->height)
	{
		x = -1;
		while (++x < image->width)
			mlx_put_pixel(image, x, y, color);
	}
}
