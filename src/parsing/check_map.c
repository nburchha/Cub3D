/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 00:13:08 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/07 08:51:15 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	floodfill(char **map, int x, int y)
{
	map[y][x] = 'X';
	if (((y > 0 && map[y - 1][x] == ' ') || (y > 0 && map[y - 1][x] == '\0')) \
	|| ((map[y + 1] && map[y + 1][x] == ' ') || (map[y + 1] && map[y + 1][x] \
	== '\0')) || ((x > 0 && map[y][x - 1] == ' ') || (x > 0 && map[y][x - 1] \
	== '\0')) || ((map[y][x + 1] && map[y][x + 1] == ' ') || (map[y][x + 1] \
	&& map[y][x + 1] == '\0')))
		return (false);
	if (y > 0 && map[y - 1][x] == '0')
		if (!floodfill(map, x, y - 1))
			return (false);
	if (map[y + 1] && map[y + 1][x] == '0')
		if (!floodfill(map, x, y + 1))
			return (false);
	if (x > 0 && map[y][x - 1] == '0')
		if (!floodfill(map, x - 1, y))
			return (false);
	if (map[y][x + 1] && map[y][x + 1] == '0')
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
	//for testing floodfill algo:
	// for (int i = 0; i < data->map->height; i++)
	// 	printf(".%s.\n", map[i]);
	return (free_split(map), true);
}

static void	save_spawn(t_data *data, int i, int j)
{
	data->map->spawn.x = j;
	data->map->spawn.y = i;
	if (data->map->map[i][j] == 'N')
			data->player.dir = 0;
	else if (data->map->map[i][j] == 'E')
		data->player.dir = M_PI / 2;
	else if (data->map->map[i][j] == 'S')
		data->player.dir = M_PI;
	else if (data->map->map[i][j] == 'W')
		data->player.dir = 3 * M_PI / 2;
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
			if (!ft_strchr("NSWE 10", map[i][j]))
				return (false);
		}
	}
	if (spawn != 1 || !check_surrounding_borders(data))
		return (false);
	return (true);
}
