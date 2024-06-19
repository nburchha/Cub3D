/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:21:29 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/19 22:49:45 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_block_minimap(mlx_image_t *img, int pos[2], int size, \
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
			if (pos[0] + i >= 0 && pos[0] + i < WIDTH && pos[1] + j >= 0 \
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
			if (i <= M_SCALE || j <= M_SCALE || i >= M_SCALE * 10 || j >= \
				M_SCALE * 10)
				mlx_put_pixel(data->minimap, j, i, 0xFFFFFFFF);
			j++;
		}
		i++;
	}
}

void	draw_player(t_data *data)
{
	t_coordinates	v[3];

	draw_circle((float [2]){M_SCALE * 5 + M_SCALE / 2, M_SCALE * 5 + M_SCALE \
				/ 2}, M_SCALE / 2, 0xFF0000FF, data->minimap);
	//calculate vertex of the triangle according to the direction of the player
	v[0] = (t_coordinates){M_SCALE * 5 + M_SCALE / 2, M_SCALE * 5 + M_SCALE / 2};
	v[1] = (t_coordinates){v[0].x + cosf(data->player.dir) * M_SCALE / 2, \
	v[0].y + sinf(data->player.dir) * M_SCALE / 2};
	v[2] = (t_coordinates){v[0].x + cosf(data->player.dir + M_PI / 2) * \
	M_SCALE / 2, v[0].y + sinf(data->player.dir + M_PI / 2) * M_SCALE / 2};
	// printf("v0: %f %f\nv1: %f %f\nv2: %f %f\n", v[0].x, v[0].y, v[1].x, v[1].y, v[2].x, v[2].y);
	// draw_line(v[0], v[1], 0xFF0000FF, data->minimap);
	draw_triangle(data, data->player.dir, 0xFF0000FF);
	// draw_filled_triangle(v[0], v[1], v[2], 0xFF0000FF, data->minimap);
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
	int		i;
	int		j;
	int		x;
	int		y;
	int		*pos;

	pos = (int [2]){data->player.pos.x / PIXEL_SIZE, data->player.pos.y / \
					PIXEL_SIZE};
	y = pos[1] - 6;
	i = 0;
	while (++y < pos[1] + 5)
	{
		x = pos[0] - 6;
		j = 0;
		while (++x < pos[0] + 5)
		{
			draw_block_minimap(data->minimap, (int [2]){j * M_SCALE, i * \
							M_SCALE}, M_SCALE, get_minimap_color(data, x, y));
			j++;
		}
		i++;
	}
	draw_player(data);
	draw_minimap_border(data);
}
