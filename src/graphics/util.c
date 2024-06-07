/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:48:48 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/07 15:41:04 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	normalize_angle(float *angle)
{
	if (*angle < 0)
		*angle += 2 * M_PI;
	if (*angle > 2 * M_PI)
		*angle -= 2 * M_PI;
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
