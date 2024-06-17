/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:14:54 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/17 20:25:45 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	save_texture(t_data *data, char *line)
{
	char			**split;
	mlx_texture_t	*texture;

	split = ft_split(line, ' ');
	if (!split)
		return (false);
	else if (!split[1])
		return (free_split(split), free(line), false);
	texture = mlx_load_png(split[1]);
	if (!texture)
		return (false);
	if (ft_strncmp(split[0], "NO", 3) == 0)
		data->n_texture = texture;
	else if (ft_strncmp(split[0], "SO", 3) == 0)
		data->s_texture = texture;
	else if (ft_strncmp(split[0], "WE", 3) == 0)
		data->w_texture = texture;
	else if (ft_strncmp(split[0], "EA", 3) == 0)
		data->e_texture = texture;
	free_split(split);
	return (true);
}

void	parse_texture(t_data *data, int fd, char *line, int *t_count)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 \
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
	{
		if (!save_texture(data, line))
			parse_error(data, fd, "Could not load texture");
		(*t_count)++;
	}
}
