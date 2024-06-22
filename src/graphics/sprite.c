/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:01:22 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/22 19:23:39 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	wasd_pressed(t_data *data)
{
	if (data->keys[MLX_KEY_W] || data->keys[MLX_KEY_A] || data->keys[MLX_KEY_S] \
		|| data->keys[MLX_KEY_D])
		return (true);
	return (false);
}

static void	draw_overlay(t_data *data, mlx_image_t *img, uint32_t x_offset, \
						uint32_t y_offset)
{
	uint32_t	i;
	uint32_t	j;

	i = -1;
	while (++i < img->height)
	{
		j = -1;
		while (++j < img->width)
		{
			if (get_color_texture(data->sprite_texture, j, i) != 0x00000000 && \
				i + y_offset >= 0 && i + y_offset < img->height && j + x_offset \
				>= 0 && j + x_offset < img->width)
				mlx_put_pixel(img, j + x_offset, i + y_offset, \
				get_color_texture(data->sprite_texture, j, i));
		}
	}
}

void	animate_sprite(t_data *data, mlx_image_t *img)
{
	static int				sign = 2;
	static int				offset = 30;

	reset_image(img, 0x00000000);
	if (offset <= 0 || offset >= 60)
		sign = -sign;
	if (data->keys[MLX_KEY_LEFT_SHIFT] && wasd_pressed(data) && offset > 2 && \
		offset < 58)
		offset += sign;
	if (wasd_pressed(data))
		offset += sign;
	draw_overlay(data, img, offset, offset / 2);
}
