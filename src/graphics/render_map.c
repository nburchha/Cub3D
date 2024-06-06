/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:48:04 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/06 12:40:50 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	calc_scale(t_data *data)
{
	if (data->map->width > data->map->height)
		data->scale = WIDTH / data->map->width;
	else
		data->scale = HEIGHT / data->map->height;
}

void	draw_block(t_data *data, int x, int y, uint32_t color)
{
	int		i;
	int		j;

	i = -1;
	while (++i < PIXEL_SIZE)
	{
		j = -1;
		while (++j < PIXEL_SIZE)
		{
			if (i == 0 || i == PIXEL_SIZE - 1 || j == 0 || j == PIXEL_SIZE - 1)
				mlx_put_pixel(data->image, x * PIXEL_SIZE + i, y * PIXEL_SIZE + j, 0xFFFFFFFF);
			else
				mlx_put_pixel(data->image, x * PIXEL_SIZE + i, y * PIXEL_SIZE + j, color);
		}
	}
}

void	render_map(t_data *data)
{
	int		x;
	int		y;

	calc_scale(data);
	y = -1;
	while (++y < data->map->height)
	{
		x = -1;
		while (++x < data->map->width)
		{
			if (data->map->map[y][x] == '1' || data->map->map[y][x] == ' ')
				draw_block(data, x, y, data->ceiling_color);
			else if (data->map->map[y][x] == '0' || data->map->map[y][x] == \
					'N' || data->map->map[y][x] == 'S' || data->map->map[y][x] \
					== 'W' || data->map->map[y][x] == 'E')
				draw_block(data, x, y, data->floor_color);
		}
	}
}
