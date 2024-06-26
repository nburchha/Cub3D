/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:40:57 by psanger           #+#    #+#             */
/*   Updated: 2024/06/26 17:50:02 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_color_texture(mlx_texture_t *texture, int x, int y)
{
	int	pixel;

	pixel = 0;
	pixel = (texture->width * y + x) * 4;
	return (get_rgba(texture->pixels[pixel], texture->pixels[pixel + 1],
			texture->pixels[pixel + 2], texture->pixels[pixel + 3]));
}

static void	get_pixel_size(t_data *data, t_dda *dda, float *pixel_size)
{
	if (dda->wall_face == 'N')
		*pixel_size = data->n_texture->width;
	if (dda->wall_face == 'O')
		*pixel_size = data->e_texture->width;
	if (dda->wall_face == 'S')
		*pixel_size = data->s_texture->width;
	if (dda->wall_face == 'W')
		*pixel_size = data->w_texture->width;
	if (dda->texture == 2)
		*pixel_size = data->door_texture->width;
}

static int	get_color(t_data *data, t_dda *dda, int y_pixel, int height)
{
	float	x;
	float	y;
	float	pixel_size;

	pixel_size = 0;
	x = 0;
	y = 0;
	get_pixel_size(data, dda, &pixel_size);
	if (dda->wall_face == 'N' || dda->wall_face == 'S')
		x = (dda->end_x - (int)dda->end_x) * pixel_size;
	if (dda->wall_face == 'O' || dda->wall_face == 'W')
		x = (dda->end_y - (int)dda->end_y) * pixel_size;
	y = ((float)y_pixel - (HEIGHT / 2 - (float)height / 2)) / (float)height
		* pixel_size;
	if (dda->texture == 2)
		return (get_color_texture(data->door_texture, (int)x, (int)y));
	if (dda->wall_face == 'N')
		return (get_color_texture(data->n_texture, (int)x, (int)y));
	if (dda->wall_face == 'O')
		return (get_color_texture(data->e_texture, (int)x, (int)y));
	if (dda->wall_face == 'S')
		return (get_color_texture(data->s_texture, (int)x, (int)y));
	if (dda->wall_face == 'W')
		return (get_color_texture(data->w_texture, (int)x, (int)y));
	return (0);
}

void	cast_projection(t_data *data, t_dda *dda, int column)
{
	float	real_len;
	float	height;
	float	real_height;
	int		y_pixel;

	real_len = fabs(cos(to_rad((float)((((float)FOV * (-1)) / 2) + (((float)FOV
								/ (float)WIDTH) * (float)column)))) * dda->len);
	height = (1500 / real_len);
	real_height = height;
	if (height > HEIGHT)
		height = HEIGHT;
	y_pixel = HEIGHT / 2 - height / 2;
	while (y_pixel < HEIGHT / 2 + height / 2)
	{
		if (y_pixel < HEIGHT && y_pixel > 0)
			mlx_put_pixel(data->image, column, y_pixel,
				get_color(data, dda, y_pixel, real_height));
		y_pixel++;
	}
}
