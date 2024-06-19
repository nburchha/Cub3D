/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:48:04 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/19 10:16:48 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_block(t_data *data, int coords[2], int size, uint32_t color)
{
	int		i;
	int		j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (coords[0] < 0 || coords[1] < 0 || coords[0] >= data->map->width \
				|| coords[1] >= data->map->height)
				continue ;
			else if (i == 0 || i == size - 1 || j == 0 || j == size - 1)
				mlx_put_pixel(data->image, coords[0] * size + i, coords[1] * \
								size + j, 0xFFFFFFFF);
			else
				mlx_put_pixel(data->image, coords[0] * size + i, coords[1] * \
								size + j, color);
		}
	}
}

void	render_map(t_data *data)
{
	int		x;
	int		y;

	y = -1;
	while (++y < data->map->height)
	{
		x = -1;
		while (++x < data->map->width)
		{
			if (data->map->map[y][x] == '1' || data->map->map[y][x] == ' ')
				draw_block(data, (int [2]){x, y}, PIXEL_SIZE, \
							data->ceiling_color);
			else if (data->map->map[y][x] == '0' || data->map->map[y][x] == \
					'N' || data->map->map[y][x] == 'S' || data->map->map[y][x] \
					== 'W' || data->map->map[y][x] == 'E')
				draw_block(data, (int [2]){x, y}, PIXEL_SIZE, \
							data->floor_color);
		}
	}
}
