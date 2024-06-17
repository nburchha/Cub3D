/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psanger <psanger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:08:59 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/17 17:46:26 by psanger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	general_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	movement(data);
	reset_image(data->image, data->mlx, 0x000000FF);
	render_map(data);
	render_player(data);
}
