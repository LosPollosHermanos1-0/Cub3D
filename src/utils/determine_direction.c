/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_direction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 02:43:36 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/25 17:10:26 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_textures	determine_direction(const t_vector_2d ray_dir, const int side)
{
	t_textures	direction;

	if (side == 0)
	{
		if (ray_dir.x < 0)
			direction = WEST;
		else
			direction = EAST;
	}
	else
	{
		if (ray_dir.y < 0)
			direction = NORTH;
		else
			direction = SOUTH;
	}
	return (direction);
}

double	calculate_distance(t_vector_2d point1, t_vector_2d point2)
{
	return (sqrt((point2.x - point1.x) * (point2.x - point1.x)
			+ (point2.y - point1.y) * (point2.y - point1.y)));
}
