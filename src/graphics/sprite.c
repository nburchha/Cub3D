/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:01:22 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/22 17:21:43 by nburchha         ###   ########.fr       */
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

static void	draw_overlay(t_data *data, mlx_image_t *img, uint32_t x_offset)
{
	uint32_t	i;
	uint32_t	j;

	i = -1;
	while (++i < img->height)
	{
		j = -1;
		while (++j < img->width)
			mlx_put_pixel(img, j + x_offset, i, \
			get_color_texture(data->sprite_texture, j, i));
	}
}

void	animate_sprite(t_data *data, mlx_image_t *img)
{
	static int				sign = 5;
	static int				offset = 50;

	reset_image(img, 0x00000000);
	if (data->keys[MLX_KEY_LEFT_SHIFT] && wasd_pressed(data))
		offset += sign;
	if (offset <= 0 || offset >= 100)
		sign = -sign;
	if (wasd_pressed(data))
		offset += sign;
	draw_overlay(data, img, offset);
}
