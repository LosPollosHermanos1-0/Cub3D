/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_player_via_mouse.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 14:53:06 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/25 17:09:07 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	*get_last_xpos(void)
{
	static double	last_xpos = -1;

	return (&last_xpos);
}

void	set_last_xpos(double xpos)
{
	double	*last_xpos;

	last_xpos = get_last_xpos();
	*last_xpos = xpos;
}

void	rotate_player_mouse(double xpos, double ypos, void *param)
{
	t_data			*data;
	double			delta_x;
	double			angle;

	(void)ypos;
	data = param;
	if (!(data->flags & FLAG_MOUSE_LOCKED))
		return ;
	if (*get_last_xpos() == -1)
	{
		set_last_xpos(xpos);
		return ;
	}
	delta_x = xpos - *get_last_xpos();
	set_last_xpos(xpos);
	angle = delta_x * 0.001;
	rotate_player(data, -angle);
	center_mouse(data);
	set_last_xpos(data->window->width / 2);
}
