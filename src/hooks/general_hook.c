/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 11:08:59 by niklasburch       #+#    #+#             */
/*   Updated: 2024/06/22 16:34:09 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	general_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	movement(data);
	reset_image(data->image, 0x000000FF);
	render_map(data);
	render_player(data);
	draw_minimap(data);
	animate_sprite(data, data->deagle);
}
