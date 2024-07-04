/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:07:59 by jmoritz           #+#    #+#             */
/*   Updated: 2024/06/26 12:08:09 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void			ft_get_pos_and_dir(e_map_elements ***map_ptr,
						t_vector_2d *pos, t_vector_2d *dir);
static t_vector_2d	ft_get_dir(e_map_elements player);

t_player	*init_player(e_map_elements ***map_ptr)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (player == NULL)
	{
		return (printf("Error: Malloc failed\n"), NULL);
		// dont exit, because map already allocated!
		// exit(1);
	}
	ft_get_pos_and_dir(map_ptr, &(player->pos), &(player->dir));
	player->plane = ft_vector_init(0, 0.66);
	player->move_speed = MOVE_SPEED;
	player->rot_speed = ROT_SPEED;
	player->wall_dist = WALL_DIST;
	return (player);
}

static void	ft_get_pos_and_dir(e_map_elements ***map_ptr,
				t_vector_2d *pos, t_vector_2d *dir)
{
	t_map	*map;
	int		row;
	int		col;

	map = static_data()->map;
	row = -1;
	while ((*map_ptr)[++row])
	{
		col = -1;
		while ((*map_ptr)[row][++col])
		{
			if ((*map_ptr)[row][col] == PLAYER_EA
				|| (*map_ptr)[row][col] == PLAYER_NO
				|| (*map_ptr)[row][col] == PLAYER_SO
				|| (*map_ptr)[row][col] == PLAYER_WE)
			{
				*pos = ft_vector_init(col, row);
				*dir = ft_get_dir((*map_ptr)[row][col]);
			}
		}
	}
}

static t_vector_2d	ft_get_dir(e_map_elements player)
{
	if (player == PLAYER_EA)
		return (ft_vector_init(1, 0));
	else if (player == PLAYER_NO)
		return (ft_vector_init(0, -1));
	else if (player == PLAYER_SO)
		return (ft_vector_init(0, 1));
	else if (player == PLAYER_WE)
		return (ft_vector_init(-1, 0));
	return (ft_vector_init(-1, -1));
}
