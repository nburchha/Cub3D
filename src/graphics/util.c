/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:48:48 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/17 20:25:45 by niklasburch      ###   ########.fr       */
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

void	reset_image(mlx_image_t *image, mlx_t *mlx, int color)
{
	int	x;
	int	y;

	y = -1;
	while (++y < mlx->height)
	{
		x = -1;
		while (++x < mlx->width)
			mlx_put_pixel(image, x, y, color);
	}
}
