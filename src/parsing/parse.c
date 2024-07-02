/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:02:04 by nburchha          #+#    #+#             */
/*   Updated: 2024/07/02 14:04:02 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
parse all textures and colors
check texture paths if they are accessible
*/

void	parse_error(t_data *data, int fd, char *msg)
{
	printf("Error\n%s\n", msg);
	if (fd != -1)
		close (fd);
	if (!data)
		exit(1);
	if (data->n_texture)
		mlx_delete_texture(data->n_texture);
	if (data->s_texture)
		mlx_delete_texture(data->s_texture);
	if (data->w_texture)
		mlx_delete_texture(data->w_texture);
	if (data->e_texture)
		mlx_delete_texture(data->e_texture);
	if (data->door_texture)
		mlx_delete_texture(data->door_texture);
	if (data->sprite_texture)
		mlx_delete_texture(data->sprite_texture);
	if (data->map->map)
		free_split(data->map->map);
	exit(1);
}

static void	check_file_ending(char *path)
{
	int	path_len;

	path_len = ft_strlen(path);
	if (ft_strncmp(path + path_len - 4, ".cub", 4) != 0)
		parse_error(NULL, -1, "No valid file ending");
}

static void	parse_texture_color(t_data *data, int fd)
{
	char	*line;
	int		t_count;
	int		c_count;

	t_count = 0;
	c_count = 0;
	line = get_next_line(fd);
	while (line && (c_count < 2 || t_count < 4))
	{
		if (ft_strchr("012", line[0]))
			break ;
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!parse_color(data, fd, line, &c_count) && \
			!parse_texture(data, fd, line, &t_count) && line[0] != '\0')
			parse_error(data, fd, "Could not parse texture or color");
		free(line);
		if (c_count == 2 && t_count == 4)
			break ;
		line = get_next_line(fd);
	}
	if (c_count < 2 || t_count < 4 || !line)
		parse_error(data, fd, "Not all requirements met inside .cub file");
}

void	parse(t_data *data, char *path)
{
	int		fd;

	check_file_ending(path);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		parse_error(NULL, -1, "Could not open file");
	parse_texture_color(data, fd);
	parse_map(data, path, fd);
	close(fd);
}
