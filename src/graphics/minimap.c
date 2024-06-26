/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:21:29 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/26 15:34:07 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_block_minimap(mlx_image_t *img, int pos[2], int size,
		int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (pos[0] + i >= 0 && pos[0] + i < WIDTH && pos[1] + j >= 0
				&& pos[1] + j < HEIGHT)
				mlx_put_pixel(img, pos[0] + i, pos[1] + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_border(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < M_SCALE * 11)
	{
		j = 0;
		while (j < M_SCALE * 11)
		{
			if (i <= M_SCALE || j <= M_SCALE || i >= M_SCALE * 10
				|| j >= M_SCALE * 10)
				mlx_put_pixel(data->minimap, j, i, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}

uint32_t	get_minimap_color(t_data *data, int x, int y)
{
	if (!valid_coords(data, x, y))
		return (0x000000FF);
	else if (data->map->map[y][x] == WALL)
		return (data->ceiling_color);
	else if (data->map->map[y][x] == DOOR)
		return (0x0000FFFF);
	return (data->floor_color);
}

void	draw_minimap(t_data *data)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	*pos;

	pos = (int [2]){data->player.pos.x / PIXEL_SIZE, data->player.pos.y
		/ PIXEL_SIZE};
	y = pos[1] - 6;
	i = 0;
	while (++y < pos[1] + 5)
	{
		x = pos[0] - 6;
		j = 0;
		while (++x < pos[0] + 5)
		{
			draw_block_minimap(data->minimap, (int [2]){j * M_SCALE, i
				* M_SCALE}, M_SCALE, get_minimap_color(data, x, y));
			j++;
		}
		i++;
	}
	draw_minimap_border(data);
	draw_player(data);
}
