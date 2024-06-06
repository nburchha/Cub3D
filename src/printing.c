/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:58:41 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/06 09:58:49 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	print_data(t_data *data)
{
	printf("n_texture: %p\n", data->n_texture);
	printf("s_texture: %p\n", data->s_texture);
	printf("w_texture: %p\n", data->w_texture);
	printf("e_texture: %p\n", data->e_texture);
	uint32_t color = data->ceiling_color;
	uint8_t r = (color >> 24) & 0xFF;
	uint8_t g = (color >> 16) & 0xFF;
	uint8_t b = (color >> 8) & 0xFF;
	printf("CEILING: Red: %u, Green: %u, Blue: %u\n", r, g, b);
	color = data->floor_color;
	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	printf("FLOOR: Red: %u, Green: %u, Blue: %u\n", r, g, b);
	//print map:
	for (int i = 0; i < data->map->height; i++)
		printf(".%s.\n", data->map->map[i]);
}
