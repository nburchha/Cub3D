/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:58:41 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/26 17:52:20 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	print_data(t_data *data)
{
	uint32_t	color;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;

	printf("n_texture: %p\n", data->n_texture);
	printf("s_texture: %p\n", data->s_texture);
	printf("w_texture: %p\n", data->w_texture);
	printf("e_texture: %p\n", data->e_texture);
	color = data->ceiling_color;
	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	printf("CEILING: Red: %u, Green: %u, Blue: %u\n", r, g, b);
	color = data->floor_color;
	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	printf("FLOOR: Red: %u, Green: %u, Blue: %u\n", r, g, b);
	// print map:
	for (int i = 0; i < data->map->height; i++)
		printf(".%s.\n", data->map->map[i]);
}
