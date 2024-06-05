/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niklasburchhardt <niklasburchhardt@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:02:04 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/05 12:05:52 by niklasburch      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
parse all textures and colors
check texture paths if they are accessible
*/

void	parse_error(t_data *data, int fd, char *msg)
{
	ft_printf("Error\n%s\n", msg);
	if (fd != -1)
		close (fd);
	if (data->n_texture)
		mlx_delete_texture(data->n_texture);
	if (data->s_texture)
		mlx_delete_texture(data->s_texture);
	if (data->w_texture)
		mlx_delete_texture(data->w_texture);
	if (data->e_texture)
		mlx_delete_texture(data->e_texture);
	exit(1);
}

void	parse(t_data *data, char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nCould not open file\n");
		exit(1);
	}
	parse_texture(data, fd);
	parse_color(data, fd);
	// parse_map(data, fd);
	close(fd);
}
