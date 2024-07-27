/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:24:54 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/27 17:33:45 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	resize_handler(int32_t width, int32_t height, void *d)
{
	t_data		*data;
	t_window	*window;

	data = d;
	window = data->window;
	mlx_resize_image(window->image, width, height);
	window->width = width;
	window->height = height;
	free(data->z_buffer);
	data->z_buffer = ft_calloc(sizeof(int) * data->window->width,
			sizeof(int));
	ft_memset(data->z_buffer, -1, sizeof(int) * data->window->width);
	if (window->image == NULL)
	{
		printf("Error: Malloc failed\n");
		exit(1);
	}
}
