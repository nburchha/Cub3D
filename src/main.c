/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:10:47 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/07 09:08:27 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_data(t_data *data, t_map *map)
{
	int	i;

	i = -1;
	while (++i < MAX_KEY)
		data->keys[i] = false;
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

static bool	init_mlx(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!data->mlx)
		return (false);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->image)
		return (false);
	return (true);
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
	if (!init_mlx(&data))
		return (ft_printf("Error\nFailed to initialize MLX\n"), 1); //TODO: handle cleanup
	render_map(&data);
	render_player(&data);
	printf("scale: %f\n", data.scale);
	mlx_image_to_window(data.mlx, data.image, 0, 0);
	mlx_key_hook(data.mlx, &keyhook, (void *)&data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0); //TODO: handle cleanup
}
