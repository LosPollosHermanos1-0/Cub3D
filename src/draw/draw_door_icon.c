/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_door_icon.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 19:38:12 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/23 19:38:16 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_door_icon(t_data *data)
{
    // (void)data;
    if (data->flags & FLAG_FACING_OPEN_DOOR)
    {
        data->window->door_icon_open->enabled = false;
        data->window->door_icon_close->enabled = true;
    }
    else if (data->flags & FLAG_FACING_CLOSED_DOOR)
    {
        data->window->door_icon_open->enabled = true;
        data->window->door_icon_close->enabled = false;
    }

    if (!(data->flags & FLAG_FACING_CLOSED_DOOR) &&
        !(data->flags & FLAG_FACING_OPEN_DOOR))
    {
        data->window->door_icon_open->enabled = false;
        data->window->door_icon_close->enabled = false;
    }
}
