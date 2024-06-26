/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:44:57 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/22 20:54:37 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	while (line && (ft_strlen(line) > 1 || line[0] != '\n'))
	{
		if (ft_strlen(line) - 1 > map->width)
			map->width = ft_strlen(line) - 1;
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		return (free(line), false);
	return (true);
}

bool	allocate_map(t_data *data, char ***allocate_to)
{
	int		i;
	char	**map;

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
	*allocate_to = map;
	(void)allocate_to;
	return (true);
}

static bool	valid_chars(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (ft_strchr(" 012NSWE", line[i]) == NULL)
			return (false);
	return (true);
}

static bool	copy_map_from_file(t_map *map, int fd)
{
	int		i;
	char	*line;

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
		if (!valid_chars(line))
			return (free(line), false);
		ft_strlcpy(map->map[i], line, ft_strlen(line) + 1);
		if (ft_strlen(line) < map->width)
			map->map[i][ft_strlen(line)] = ' ';
		free(line);
		line = get_next_line(fd);
	}
	return (true);
}

void	parse_map(t_data *data, char *path, int fd)
{
	if (!get_map_size(path, data->map))
		parse_error(data, fd, "Could not get map size");
	if (!allocate_map(data, &data->map->map))
		parse_error(data, fd, "Malloc failed");
	if (!copy_map_from_file(data->map, fd))
		parse_error(data, fd, "Could not copy map from file");
	if (!check_map(data))
		parse_error(data, fd, "The map doesnt fulfill all criteria");
}
