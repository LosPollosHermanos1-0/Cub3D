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

uint32_t get_pixel(const mlx_texture_t* texture, uint32_t x, uint32_t y) {
    if (x >= texture->width || y >= texture->height) {
        // Coordinates are outside the texture bounds, return a default color or error code.
        // Here, 0 is returned as an error code, assuming 0 is not a valid color in your context.
        return 0;
    }

    // Calculate the position in the pixel array.
    // Assuming the texture is stored in a 1D array and each pixel is represented by 4 bytes (RGBA).
    uint32_t index = (y * texture->width + x) * texture->bytes_per_pixel;

    // Assuming the color format is RGBA, construct the color from the pixel array.
    // This assumes that the texture's pixel data is stored as unsigned bytes in RGBA order.
    uint32_t color = (texture->pixels[index] << 24) | (texture->pixels[index + 1] << 16) |
                     (texture->pixels[index + 2] << 8) | texture->pixels[index + 3];

    return color;
}
