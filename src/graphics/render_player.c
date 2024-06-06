/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:23:37 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/06 10:58:26 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_circle(float x, float y, uint32_t color, t_data *data)
{
	float	radius;
	float	dist;
	int		i;
	int		j;

	radius = data->scale / 4;
	i = -1;
	while (++i < data->scale)
	{
		j = -1;
		while (++j < data->scale)
		{
			dist = sqrtf((i - radius) * (i - radius) + (j - radius) * (j - radius));
			if (dist < radius)
				mlx_put_pixel(data->image, x * data->scale + i + radius, y * data->scale + j + radius, color);
		}
	}
}

void	render_player(t_data *data)
{
	draw_circle(data->player.pos.x, data->player.pos.y, 0xFF0000FF, data);
	
}