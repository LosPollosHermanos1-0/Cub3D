/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:12:47 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/04 13:17:06 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_window	*init_window(void)
{
	t_window	*window;

	window = malloc(sizeof(t_window));
	window->mlx = mlx_init(WINDOW_W_INIT, WINDOW_H_INIT, "Cub3D", true);
	if (window->mlx == NULL)
		return (printf("Error: window mlx not allocated\n"), NULL);
	window->image = mlx_new_image(window->mlx, WINDOW_W_INIT, WINDOW_H_INIT);
	if (window->image == NULL)
		return (printf("Error: window image not allocated\n"), NULL);
	window->width = WINDOW_W_INIT;
	window->height = WINDOW_H_INIT;
	return (window);
}
