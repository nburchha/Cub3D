/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:16:52 by niklasburch       #+#    #+#             */
/*   Updated: 2024/07/02 15:35:10 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_digit_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (false);
	return (true);
}

static bool	convert_to_int(char **rgb_char, uint32_t *color)
{
	int	rgb[3];
	int	i;

	i = -1;
	while (rgb_char[++i] && i < 3)
	{
		if (!is_digit_str(rgb_char[i]))
			return (false);
		rgb[i] = ft_atoi(rgb_char[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (false);
	}
	if (i != 3 || *color != 0)
		return (false);
	*color = ((uint32_t)rgb[0] << 24 | (uint32_t)rgb[1] << 16 | \
			(uint32_t)rgb[2] << 8 | 0xFF);
	return (true);
}

static bool	extract_color(t_data *data, char *line)
{
	char	**split;
	char	**rgb_char;

	split = ft_split(line, ' ');
	if (!split)
		return (false);
	if (!split[1] || split[2])
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

bool	parse_color(t_data *data, int fd, char *line, int *c_count)
{
	if (ft_strncmp(line, "C ", 2) == 0 || ft_strncmp(line, "F ", 2) == 0)
	{
		if (!extract_color(data, line))
		{
			if (line)
				free(line);
			parse_error(data, fd, "Could not extract color");
		}
		(*c_count)++;
		return (true);
	}
	return (false);
}
