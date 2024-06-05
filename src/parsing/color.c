/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:16:52 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/05 12:20:23 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static bool	convert_to_int(char **rgb_char, uint32_t *color)
{
	int	rgb[3];
	int	i;

	i = -1;
	while (rgb_char[++i] && i < 3)
	{
		rgb[i] = ft_atoi(rgb_char[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (false);
	}
	if (i != 3)
		return (false);
	*color = (0xFF << 24 | (uint32_t)rgb[0] << 16 | (uint32_t)rgb[1] << 8 | (uint32_t)rgb[2]);
	return (true);
}

static bool	extract_color(t_data *data, char *line)
{
	char	**split;
	char	**rgb_char;

	split = ft_split(line, ' ');
	if (!split)
		return (false);
	if (!split[1])
		return (free_split(split), false);
	rgb_char = ft_split(split[1], ',');
	if (!rgb_char)
		return (free_split(split), false);
	if (!rgb_char[0] || !rgb_char[1] || !rgb_char[2] || rgb_char[3])
		return (free_split(split), free_split(rgb_char), false);
	if (split[0][0] == 'C')
		if (!convert_to_int(rgb_char, &data->ceiling_color))
			return (free_split(split), free_split(rgb_char), false);
	if (split[0][0] == 'F')
		if (!convert_to_int(rgb_char, &data->floor_color))
			return (free_split(split), free_split(rgb_char), false);
	free_split(split);
	free_split(rgb_char);
	return (true);
}

void	parse_color(t_data *data, int fd)
{
	char	*line;
	int		colors;

	colors = 0;
	line = get_next_line(fd);
	while (line && colors < 2)
	{
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0)
		{
			if (!extract_color(data, line))
				parse_error(data, fd, "Could not extract color");
			colors++;
		}
		free(line);
		line = get_next_line(fd);
	}
}
