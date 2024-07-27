/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:12:47 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/27 17:34:38 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_window_values(t_window *window);

void	add_images_to_window(t_window *window)
{
	mlx_image_to_window(window->mlx, window->image, 0, 0);
	mlx_image_to_window(window->mlx, window->mini_image, 0, 0);
	mlx_image_to_window(window->mlx, window->door_icon_open,
		window->width / 2 - window->door_icon_width / 2,
		window->height / 2 - window->door_icon_height / 2);
	mlx_image_to_window(window->mlx, window->door_icon_close,
		window->width / 2 - window->door_icon_width / 2,
		window->height / 2 - window->door_icon_height / 2);
	window->door_icon_close->enabled = false;
	window->door_icon_open->enabled = false;
}

t_window	*init_window(void)
{
	t_window		*window;

	window = malloc(sizeof(t_window));
	window->mlx = mlx_init(WINDOW_W_INIT, WINDOW_H_INIT, "Cub3D", true);
	if (window->mlx == NULL)
		return (printf("Error: window mlx not allocated\n"), NULL);
	window->image = mlx_new_image(window->mlx, WINDOW_W_INIT, WINDOW_H_INIT);
	window->mini_image = mlx_new_image(window->mlx,
			MINI_IMAGE_W, MINI_IMAGE_H);
	if (window->image == NULL || window->mini_image == NULL)
		return (printf("Error: window image not allocated\n"), NULL);
	window->close_texture = mlx_load_png("textures/door-close-icon.png");
	window->door_icon_open = mlx_texture_to_image(window->mlx,
			window->close_texture);
	window->open_texture = mlx_load_png("textures/door-open-icon.png");
	window->door_icon_close = mlx_texture_to_image(window->mlx,
			window->open_texture);
	if (window->door_icon_open == NULL || window->door_icon_close == NULL)
		return (printf("Error: door icon not allocated\n"), NULL);
	fill_window_values(window);
	add_images_to_window(window);
	return (window);
}

static void	fill_window_values(t_window *window)
{
	window->width = WINDOW_W_INIT;
	window->height = WINDOW_H_INIT;
	window->mini_width = MINI_IMAGE_W;
	window->mini_height = MINI_IMAGE_H;
	window->door_icon_width = DOOR_ICON_W;
	window->door_icon_height = DOOR_ICON_H;
}
