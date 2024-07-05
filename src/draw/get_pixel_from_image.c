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

inline uint32_t	get_pixel(const mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	const uint32_t	index = (y * texture->width + x) * texture->bytes_per_pixel;
	const uint8_t	*pixel_address = texture->pixels + index;

	if (x >= texture->width || y >= texture->height)
		return (0);
	return ((pixel_address[0] << 24)
		| (pixel_address[1] << 16)
		| (pixel_address[2] << 8)
		| pixel_address[3]);
}
