/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_from_image.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:32:39 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/22 21:05:40 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

inline uint32_t	get_pixel(const mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	uint32_t	index;
	uint8_t		*pixel_address;

	if (x >= texture->width || y >= texture->height)
		return (0);
	index = (y * texture->width + x) * texture->bytes_per_pixel;
	pixel_address = texture->pixels + index;
	return (((uint32_t)pixel_address[0] << 24)
		| ((uint32_t)pixel_address[1] << 16)
		| ((uint32_t)pixel_address[2] << 8)
		| (uint32_t)pixel_address[3]);
}
