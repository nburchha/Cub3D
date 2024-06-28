/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:10:47 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/28 10:40:19 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_data(t_data *data, t_map *map)
{
	int			i;
	t_minimap_p	mini;

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
	init_minimap_player(&mini);
	data->minimap_player = mini;
}

static bool	init_mlx(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!data->mlx)
		return (false);
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->minimap = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->deagle = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->image || !data->minimap || !data->deagle)
		return (false);
	if (BONUS)
	{
		data->door_texture = mlx_load_png(DOOR_PATH);
		if (!data->door_texture)
			parse_error(data, -1, "Could not load texture\n");
		data->sprite_texture = mlx_load_png(SPRITE_PATH);
		if (!data->sprite_texture)
			parse_error(data, -1, "Could not load texture\n");
	}
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	mlx_image_to_window(data->mlx, data->minimap, 0, 0);
	data->deagle = mlx_texture_to_image(data->mlx, data->sprite_texture);
	mlx_image_to_window(data->mlx, data->deagle, WIDTH - 1000, HEIGHT - 648);
	return (true);
}

static void	cleanup(t_data *data)
{
	if (data->sprite_texture)
		mlx_delete_texture(data->sprite_texture);
	if (data->door_texture)
		mlx_delete_texture(data->door_texture);
	if (data->n_texture)
		mlx_delete_texture(data->n_texture);
	if (data->s_texture)
		mlx_delete_texture(data->s_texture);
	if (data->w_texture)
		mlx_delete_texture(data->w_texture);
	if (data->e_texture)
		mlx_delete_texture(data->e_texture);
	if (data->map->map)
		free_split(data->map->map);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_map	map;

	if (argc != 2)
		return (printf("Error\nInvalid number of arguments\n"), 1);
	init_data(&data, &map);
	parse(&data, argv[1]);
	if (!init_mlx(&data))
		return (printf("Error\nFailed to initialize MLX\n"),
			mlx_terminate(data.mlx), 1);
	render_player(&data);
	mlx_key_hook(data.mlx, &keyhook, (void *)&data);
	mlx_loop_hook(data.mlx, &general_hook, (void *)&data);
	mlx_cursor_hook(data.mlx, &cursor_hook, (void *)&data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (cleanup(&data), 0);
}
