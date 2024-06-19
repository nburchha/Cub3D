/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nburchha <nburchha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 21:07:57 by nburchha          #+#    #+#             */
/*   Updated: 2024/06/19 21:08:29 by nburchha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Function to sort vertices by their y-coordinates
void	sort_vertices_by_y(t_coordinates *v0, t_coordinates *v1,
		t_coordinates *v2)
{
	t_coordinates	temp;

	if (v0->y > v1->y)
	{
		temp = *v0;
		*v0 = *v1;
		*v1 = temp;
	}
	if (v0->y > v2->y)
	{
		temp = *v0;
		*v0 = *v2;
		*v2 = temp;
	}
	if (v1->y > v2->y)
	{
		temp = *v1;
		*v1 = *v2;
		*v2 = temp;
	}
}

// Function to draw a filled triangle
void	draw_filled_triangle(t_coordinates v0, t_coordinates v1,
		t_coordinates v2, uint32_t color, mlx_image_t *img)
{
	float	curx1;
	float	curx2;

	sort_vertices_by_y(&v0, &v1, &v2);
	float dx1, dx2, dx3;
	if (v1.y - v0.y > 0)
	{
		dx1 = (v1.x - v0.x) / (v1.y - v0.y);
	}
	else
	{
		dx1 = 0;
	}
	if (v2.y - v0.y > 0)
	{
		dx2 = (v2.x - v0.x) / (v2.y - v0.y);
	}
	else
	{
		dx2 = 0;
	}
	if (v2.y - v1.y > 0)
	{
		dx3 = (v2.x - v1.x) / (v2.y - v1.y);
	}
	else
	{
		dx3 = 0;
	}
	curx1 = v0.x;
	curx2 = v0.x;
	for (int y = v0.y; y <= v2.y; y++)
	{
		if (y < v1.y)
		{
			if (dx1 < dx2)
			{
				draw_line((t_coordinates){curx1, y}, (t_coordinates){curx2, y},
					color, img);
			}
			else
			{
				draw_line((t_coordinates){curx2, y}, (t_coordinates){curx1, y},
					color, img);
			}
			curx1 += dx1;
			curx2 += dx2;
		}
		else
		{
			if (dx3 < dx2)
			{
				draw_line((t_coordinates){curx1, y}, (t_coordinates){curx2, y},
					color, img);
			}
			else
			{
				draw_line((t_coordinates){curx2, y}, (t_coordinates){curx1, y},
					color, img);
			}
			curx1 += dx3;
			curx2 += dx2;
		}
	}
}
