/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:10:47 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/06 01:27:29 by niklasburch      ###   ########.fr       */
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
	uint8_t r = (color >> 16) & 0xFF;
	uint8_t g = (color >> 8) & 0xFF;
	uint8_t b = color & 0xFF;

	printf("CEILING: Red: %u, Green: %u, Blue: %u\n", r, g, b);
	color = data->floor_color;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;

	printf("FLOOR: Red: %u, Green: %u, Blue: %u\n", r, g, b);
}

static void	init_data(t_data *data, t_map *map)
{
	map->map = NULL;
	map->height = 0;
	map->width = 0;
	data->ceiling_color = 0;
	data->floor_color = 0;
	data->n_texture = NULL;
	data->s_texture = NULL;
	data->w_texture = NULL;
	data->e_texture = NULL;
	data->map = map;
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_map	map;

	if (argc != 2)
		return (ft_printf("Error\nInvalid number of arguments\n"), 1);
	init_data(&data, &map);
	parse(&data, argv[1]);
	print_data(&data);

	return (0);
}
