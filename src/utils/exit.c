/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:15:48 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/04 16:35:27 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

// void free_data(t_data *data) {
//     free(data->player);
//     free(data->window);
//     free(data->map);
//     free(data);
// }


void ft_exit()
{
	t_data		*data;

	mlx_terminate(static_data()->window->mlx);
	data = static_data();
	free_data(&data);
	exit(0);
}
