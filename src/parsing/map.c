/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:44:57 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/06 00:10:22 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
1. get map size
2. allocate memory for map
3. fill map with spaces
4. fill map with actual map
5. check if map is valid
*/

static bool	get_map_size(char *path, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	line = get_next_line(fd);
	while (line && line[0] != ' ' && line[0] != '1' && line[0] != '0')
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line && ft_strlen(line) > 1)
	{
		if (ft_strlen(line) - 1 > map->width)
			map->width = ft_strlen(line) - 1;
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (true);
}

static bool	allocate_map(t_data *data)
{
	int	i;
	char **map;

	map = malloc((data->map->height + 1) * sizeof(char *));
	if (!map)
		return (false);
	map[data->map->height] = NULL;
	i = -1;
	while (++i < data->map->height)
	{
		map[i] = ft_calloc((data->map->width + 1), sizeof(char));
		if (!map[i])
			return (free_split(map), false);
		ft_memset(map[i], ' ', data->map->width);
	}
	data->map->map = map;
	return (true);
}

static void	copy_map_from_file(t_map *map, int fd)
{
	int	i;
	char *line;

	i = -1;
	line = get_next_line(fd);
	while (line && ft_strlen(line) == 1)
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line && map->map[++i])
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		ft_strlcpy(map->map[i], line, ft_strlen(line) + 1);
		if (ft_strlen(line) < map->width)
			map->map[i][ft_strlen(line)] = ' ';
		free(line);
		line = get_next_line(fd);
	}
}

void	parse_map(t_data *data, char *path, int fd)
{
	if (!get_map_size(path, data->map))
		parse_error(data, fd, "Open failed");
	printf("map height: %d, width: %d\n", data->map->height, data->map->width);
	if (!allocate_map(data))
		parse_error(data, fd, "Malloc failed");
	copy_map_from_file(data->map, fd);
	for (int i = 0; i < data->map->height; i++)
		printf(".%s.\n", data->map->map[i]);
	
}
