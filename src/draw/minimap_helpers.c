/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:47:26 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/25 08:57:39 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Checks if point is in player
 * @param point point to check
 * @param a corner a of player
 * @param b corner b of player
 * @param c corner c of player
 */
bool	ft_is_point_in_triangle(t_vector_2d *point, t_vector_2d *a,
		t_vector_2d *b, t_vector_2d *c)
{
	double	denominator;
	double	alpha;
	double	beta;
	double	gamma;

	denominator = ((b->y - c->y) * (a->x - c->x)
			+ (c->x - b->x) * (a->y - c->y));
	alpha = ((b->y - c->y) * (point->x - c->x)
			+ (c->x - b->x) * (point->y - c->y)) / denominator;
	beta = ((c->y - a->y) * (point->x - c->x)
			+ (a->x - c->x) * (point->y - c->y)) / denominator;
	gamma = 1.0 - alpha - beta;
	return ((alpha > 0) && (beta > 0) && (gamma > 0));
}

/**
 * Checks if point is in circle
 * @param center center of circle
 * @param radius radius of circle
 * @param point point to check
 */
bool	ft_is_point_in_circle(t_vector_2d center, double radius,
		t_vector_2d point)
{
	return (pow(point.x - center.x, 2) + pow(point.y - center.y, 2)
		<= pow(radius, 2));
}
