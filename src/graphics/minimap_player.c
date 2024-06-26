/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:07:57 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/20 15:00:16 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_filled_triangle(mlx_image_t *img, t_coordinates pos, float direction)
{
	int	i;
	int	j;
	int	line_len;

	i = 0;
	line_len = 0;
	pos.x = M_SCALE * 5;// + M_SCALE / 2;
	pos.y = M_SCALE * 5;// + M_SCALE / 2;
	int center_x = pos.x + M_SCALE / 2;
	int center_y = pos.y + M_SCALE / 2;
	direction = normalize_angle(-direction);
	draw_circle((float [2]){center_x, center_y}, M_SCALE / 8, 0xFFFFFFFF, img);
	while (i < M_SCALE * 2)
	{
		if (i % 2 == 0)
			line_len++;
		j = line_len;
		while (j < M_SCALE - line_len)
		{
			int rotated_x = (int)(center_x + (pos.x - center_x + j) * cos(direction) - (pos.y - center_y + i) * sin(direction));
			int rotated_y = (int)(center_y + (pos.x - center_x + j) * sin(direction) + (pos.y - center_y + i) * cos(direction));
			mlx_put_pixel(img, rotated_x, rotated_y, 0xFF0000FF);
			j++;
		}
		i++;
	}
	(void)direction;
}
