/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:23:37 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/19 17:58:46 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_circle(float coords[2], float radius, uint32_t color, mlx_image_t *img)
{
	float	dist;
	int		i;
	int		j;

	i = -1;
	while (++i < PIXEL_SIZE)
	{
		j = -1;
		while (++j < PIXEL_SIZE)
		{
			dist = sqrtf((i - radius) * (i - radius) + (j - radius) * (j
						- radius));
			if (dist < radius)
				mlx_put_pixel(img, coords[0] + i - radius, coords[1] + \
								j - radius, color);
		}
	}
}

void	draw_line(t_coordinates start, t_coordinates end, uint32_t color,
		t_data *data)
{
	float	dx;
	float	dy;
	float	step;
	float	x;
	float	y;

	dx = end.x - start.x;
	dy = end.y - start.y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx /= step;
	dy /= step;
	x = start.x;
	y = start.y;
	while ((int)(x - end.x) || (int)(y - end.y))
	{
		mlx_put_pixel(data->image, x, y, color);
		x += dx;
		y += dy;
	}
}

float	to_rad(int angle)
{
	return (M_PI / 180 * angle);
}

int	get_rgba(int r, int g, int b, int a)
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

int	get_color(t_data *data, t_dda *dda, int y_pixel, int height)
{
	float	x;
	float	y;

	x = 0;
	y = 0;
	if (dda->wall_face == 'N' || dda->wall_face == 'S')
		x = (dda->end_x - (int)dda->end_x) * PIXEL_SIZE;
	if (dda->wall_face == 'O' || dda->wall_face == 'W')
		x = (dda->end_y - (int)dda->end_y) * PIXEL_SIZE;
	y = ((float)y_pixel - (HEIGHT / 2 - (float)height / 2)) / (float)height
		* (float)PIXEL_SIZE;
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

void	cast(t_data *data, t_dda *dda, int column)
{
	float	real_len;
	float	height;
	float	real_height;
	int		color;
	int		mid;

	real_len = fabs(cos(to_rad((float)((((float)FOV * (-1)) / 2) + (((float)FOV
								/ (float)WIDTH) * (float)column)))) * dda->len);
	height = (1500 / real_len);
	real_height = height;
	if (height > HEIGHT)
		height = HEIGHT;
	color = 0;
	mid = HEIGHT / 2;
	for (int y_pixel = mid - height / 2; y_pixel < mid + height / 2; y_pixel++)
	{
		if (y_pixel < HEIGHT && y_pixel > 0)
		{
			color = get_color(data, dda, y_pixel, real_height);
			mlx_put_pixel(data->image, column, y_pixel, color);
		}
	}
}

void	render_player(t_data *data)
{
	float	ray_angle;
	int		column;
	t_dda	dda;

	ray_angle = data->player.dir - (FOV / 2) * (M_PI / 180);
	column = 0;
	reset_canvas(data);
	draw_circle((float [2]){data->player.pos.x, data->player.pos.y}, PIXEL_SIZE / \
				8, 0xFF0000FF, data->image);
	while (ray_angle <= data->player.dir + ((FOV / 2) * (M_PI / 180)))
	{
		dda_algo(&dda, data, normalize_angle(ray_angle));
		cast(data, &dda, column);
		ray_angle += (FOV) * (M_PI / 180) / WIDTH;
		column++;
	}
}
