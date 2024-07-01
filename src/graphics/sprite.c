/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:01:22 by nburchha          #+#    #+#             */
/*   Updated: 2024/07/01 23:28:32 by niklasburch      ###   ########.fr       */
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
	static int				offset = 40;

	reset_image(img, 0x00000000);
	if ((offset <= 10 && sign < 0) || (offset >= 70 && sign > 0))
		sign = -sign;
	if (data->keys[MLX_KEY_LEFT_SHIFT] && wasd_pressed(data) && offset > 12 && \
		offset < 68)
		offset += sign;
	if (wasd_pressed(data))
		offset += sign;
	draw_overlay(data, img, offset, (offset - 10) / 2);
}
