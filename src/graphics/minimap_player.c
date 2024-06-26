/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:07:57 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/26 17:27:33 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_point_in_triangle(t_coordinates p, t_coordinates a, t_coordinates b,
		t_coordinates c)
{
	float	denominator;
	float	alpha;
	float	beta;
	float	gamma;

	denominator = ((b.y - c.y) * (a.x - c.x) + (c.x - b.x) * (a.y - c.y));
	alpha = ((b.y - c.y) * (p.x - c.x) + (c.x - b.x) * (p.y - c.y))
		/ denominator;
	beta = ((c.y - a.y) * (p.x - c.x) + (a.x - c.x) * (p.y - c.y))
		/ denominator;
	gamma = 1.0 - alpha - beta;
	return ((alpha > 0) && (beta > 0) && (gamma > 0));
}

void	get_pos_angle(float *x, float *y, t_data *data)
{
	float	delta_x;
	float	delta_y;
	float	len;
	float	angle_norm;

	delta_x = *x - (float)data->minimap_player.start_x;
	delta_y = *y - (float)data->minimap_player.start_y;
	len = pow(pow(delta_x, 2) + pow(delta_y, 2), 0.5);
	angle_norm = atan2(delta_x, delta_y);
	*x = cos(-data->player.dir + M_PI + angle_norm) * len
		+ (float)data->minimap_player.start_x;
	*y = sin(-data->player.dir + M_PI + angle_norm) * len
		+ (float)data->minimap_player.start_y;
}

void	init_minimap_player(t_minimap_p *mini)
{
	mini->height = 18;
	mini->width = mini->height / 1.5;
	mini->size = mini->height;
	if (mini->height < mini->width)
		mini->size = mini->width;
	mini->size += 2;
	mini->start_x = 88;
	mini->start_y = 88;
	mini->top.x = 0;
	mini->top.y = 0;
	mini->left.x = 0;
	mini->left.y = 0;
	mini->right.x = 0;
	mini->right.y = 0;
	mini->p.x = 0;
	mini->p.y = 0;
}

void	adjust_corner_pos(t_data *data)
{
	data->minimap_player.top.x = data->minimap_player.start_x;
	data->minimap_player.top.y = data->minimap_player.start_y
		- data->minimap_player.height / 2;
	get_pos_angle(&data->minimap_player.top.x, &data->minimap_player.top.y,
		data);
	data->minimap_player.left.x = data->minimap_player.start_x
		- data->minimap_player.width / 2;
	data->minimap_player.left.y = data->minimap_player.start_y
		+ data->minimap_player.height / 2;
	get_pos_angle(&data->minimap_player.left.x, &data->minimap_player.left.y,
		data);
	data->minimap_player.right.x = data->minimap_player.start_x
		+ data->minimap_player.width / 2;
	data->minimap_player.right.y = data->minimap_player.start_y
		+ data->minimap_player.height / 2;
	get_pos_angle(&data->minimap_player.right.x, &data->minimap_player.right.y,
		data);
}

void	draw_player(t_data *data)
{
	int	i;
	int	j;

	adjust_corner_pos(data);
	i = data->minimap_player.start_y - data->minimap_player.size;
	j = data->minimap_player.start_x - data->minimap_player.size;
	while (i < data->minimap_player.start_y + data->minimap_player.size)
	{
		j = data->minimap_player.start_x - data->minimap_player.size;
		while (j < data->minimap_player.start_x + data->minimap_player.size)
		{
			data->minimap_player.p.x = j;
			data->minimap_player.p.y = i;
			if (is_point_in_triangle(data->minimap_player.p,
					data->minimap_player.top, data->minimap_player.left,
					data->minimap_player.right))
			{
				if (i < HEIGHT && i > 0 && j < WIDTH && j > 0)
					mlx_put_pixel(data->minimap, j, i, 0xFF0000FF);
			}
			j++;
		}
		i++;
	}
}
