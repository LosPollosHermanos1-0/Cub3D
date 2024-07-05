/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:15:48 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/02 19:16:14 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void free_data(t_data *data) {
    free(data->player);
    free(data->window);
    free(data->map);
    free(data);
}


void ft_exit() {
    mlx_terminate(static_data()->window->mlx);
    free_data(static_data());
    exit(0);
}