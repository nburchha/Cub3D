/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:48:04 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/06 10:46:53 by niklasburch      ###   ########.fr       */
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
	while (++i < data->scale)
	{
		j = -1;
		while (++j < data->scale)
		{
			if (i == 0 || i == data->scale - 1 || j == 0 || j == data->scale - 1)
				mlx_put_pixel(data->image, x * data->scale + i, y * data->scale + j, 0xFFFFFFFF);
			else
				mlx_put_pixel(data->image, x * data->scale + i, y * data->scale + j, color);
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
