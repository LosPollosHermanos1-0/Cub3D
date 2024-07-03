/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_from_image.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:32:39 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/02 23:33:05 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	create_color(const uint8_t r, const uint8_t g, const uint8_t b,
		const uint8_t alpha)
{
	return ((r << 24) | (g << 16) | (b << 8) | alpha);
}

uint32_t	get_pixel(const mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	const uint32_t	index = (y * texture->width + x) * texture->bytes_per_pixel;

	if (x >= texture->width || y >= texture->height)
		return (0);
	return (create_color(texture->pixels[index], texture->pixels[index + 1],
			texture->pixels[index + 2], texture->pixels[index + 3]));
}
