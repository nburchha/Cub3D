/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_canvas.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:08:05 by psanger           #+#    #+#             */
/*   Updated: 2024/06/18 15:58:02 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int32_t ft_pixel(int32_t color_code)
{
	return (color_code << 8 | 0xFF);
}

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
			mlx_put_pixel(data->image, x, y, ft_pixel(data->ceiling_color));
			x++;
		}
		x = 0;
		y++;
	}
	while (y <= HEIGHT - 1)
	{
		while (x <= WIDTH - 1)
		{
			mlx_put_pixel(data->image, x, y, ft_pixel(data->floor_color));
			x++;
		}
		x = 0;
		y++;
	}
}

