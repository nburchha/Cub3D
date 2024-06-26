/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:13:08 by niklasburch       #+#    #+#             */
/*   Updated: 2024/07/01 17:22:32 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	floodfill(char **map, int x, int y)
{
	map[y][x] = 'X';
	if (((y <= 0 || map[y - 1][x] == ' ' || map[y - 1][x] == '\0')) \
	|| ((!map[y + 1] || map[y + 1][x] == ' ' || map[y + 1][x] \
	== '\0')) || ((x <= 0 || map[y][x - 1] == ' ' || map[y][x - 1] \
	== '\0')) || ((!map[y][x + 1] || map[y][x + 1] == ' ' || \
	map[y][x + 1] == '\0')))
		return (false);
	if (y > 0 && (map[y - 1][x] == FLOOR || map[y - 1][x] == DOOR))
		if (!floodfill(map, x, y - 1))
			return (false);
	if (map[y + 1] && (map[y + 1][x] == FLOOR || map[y + 1][x] == DOOR))
		if (!floodfill(map, x, y + 1))
			return (false);
	if (x > 0 && (map[y][x - 1] == FLOOR || map[y][x - 1] == DOOR))
		if (!floodfill(map, x - 1, y))
			return (false);
	if (map[y][x + 1] && (map[y][x + 1] == FLOOR || map[y][x + 1] == DOOR))
		if (!floodfill(map, x + 1, y))
			return (false);
	return (true);
}

static bool	check_surrounding_borders(t_data *data)
{
	char	**map;
	int		i;

	if (!allocate_map(data, &map))
		return (false);
	i = -1;
	while (data->map->map[++i])
		ft_memcpy(map[i], data->map->map[i], data->map->width);
	if (!floodfill(map, data->map->spawn.x, data->map->spawn.y))
		return (free_split(map), false);
	return (free_split(map), true);
}

static void	save_spawn(t_data *data, int i, int j)
{
	data->map->spawn.x = j;
	data->map->spawn.y = i;
	data->player.pos.x = j * PIXEL_SIZE + PIXEL_SIZE / 2;
	data->player.pos.y = i * PIXEL_SIZE + PIXEL_SIZE / 2;
	if (data->map->map[i][j] == 'N')
		data->player.dir = M_PI / 2;
	else if (data->map->map[i][j] == 'E')
		data->player.dir = 0;
	else if (data->map->map[i][j] == 'S')
		data->player.dir = 3 * M_PI / 2;
	else if (data->map->map[i][j] == 'W')
		data->player.dir = M_PI;
}

bool	check_map(t_data *data)
{
	char	**map;
	int		i;
	int		j;
	int		spawn;

	map = data->map->map;
	i = -1;
	spawn = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr("NSWE", map[i][j]) && ++spawn > 0)
				save_spawn(data, i, j);
			if (!ft_strchr("NSWE 102", map[i][j]))
				return (false);
		}
	}
	if (spawn != 1 || !check_surrounding_borders(data))
		return (false);
	return (true);
}
