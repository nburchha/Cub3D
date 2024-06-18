/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:21:29 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/18 18:15:39 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	near_player(t_data *data, int x, int y)
{
	float	player_x;
	float	player_y;
	float	dist;

	player_x = data->player.pos.x / PIXEL_SIZE;
	player_y = data->player.pos.y / PIXEL_SIZE;
	dist = sqrtf((player_x - x) * (player_x - x) + (player_y - y) * (player_y - y));
	if (dist < 5.0)
		return (true);
	return (false);
}

void	draw_minimap(t_data *data)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = 0;
	x = PIXEL_SIZE;
	y = PIXEL_SIZE;
	while (i < data->map->height)
	{
		j = 0;
		while (j < data->map->width)
		{
			x = 
			// x = PIXEL_SIZE * 2 + ((float)j - data->player.pos.x / PIXEL_SIZE) * MINIMAP_SIZE;
			// y = PIXEL_SIZE * 2 + ((float)i - data->player.pos.y / PIXEL_SIZE) * MINIMAP_SIZE;
			printf("x: %d, y: %d\n", x, y);
			if (data->map->map[i][j] == WALL && near_player(data, j, i))
				draw_block(data, (int [2]){x, y}, MINIMAP_SIZE, data->ceiling_color);
			else if (data->map->map[i][j] == DOOR && near_player(data, j, i))
				draw_block(data, (int [2]){x, y}, MINIMAP_SIZE, 0xFF00FFFF);
			else if (near_player(data, j, i))
				draw_block(data, (int [2]){x, y}, MINIMAP_SIZE, data->floor_color);
			j++;
		}
		i++;
	}
}
