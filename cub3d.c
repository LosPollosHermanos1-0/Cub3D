/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:42:07 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/23 16:17:58 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	leak_check(void)
{
	system("leaks cub3D");
}

int	main(int argc, char **argv)
{
	t_data	*data;

	// mlx_set_setting(MLX_HEADLESS, true);
	if (LEAKS)
		atexit(leak_check);
	if (ft_validate_input(argc, &argv) == false)
		return (1);
	// mlx_set_setting(MLX_DECORATED, 0);
	data = static_data();
	// init_data();
	if (ft_set_data(&(argv[1])) == false)
		return (1);
	draw_rays();
	mlx_image_to_window(data->window->mlx, data->window->image, 0, 0);
	mlx_image_to_window(data->window->mlx, data->window->mini_image, 0, 0);
	mlx_loop_hook(data->window->mlx, wasd_key_input, data);
	mlx_set_cursor_mode(data->window->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(data->window->mlx, WINDOW_H_INIT / 2, WINDOW_W_INIT / 2);
	mlx_cursor_hook(data->window->mlx, &mouse_move_callback, data);
	mlx_mouse_hook(data->window->mlx, mouse_click_handler, data);
	mlx_key_hook(data->window->mlx, key_handler, data);
	mlx_resize_hook(data->window->mlx, resize_handler, data);
	mlx_loop(data->window->mlx);
	mlx_terminate(data->window->mlx);
	return (0);
}
