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

static void			ft_get_pos_and_dir(t_vector_2d *pos, t_vector_2d *dir);
static t_vector_2d	ft_get_dir(e_map_elements player);

t_player	*init_player()
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (player == NULL) {
		printf("Error: Malloc failed\n");
		exit(1);
	}
	ft_get_pos_and_dir(&(player->pos), &(player->dir));
	player->plane = ft_vector_init(0, 0.66);
	player->move_speed = MOVE_SPEED;
	player->rot_speed = ROT_SPEED;
	player->wall_dist = WALL_DIST;
	return (player);
}

static void	ft_get_pos_and_dir(t_vector_2d *pos, t_vector_2d *dir)
{
	t_map	*map;
	int		row;
	int		col;

	map = static_data()->map;
	row = -1;
	while (map->map[++row])
	{
		col = -1;
		while (map->map[row][++col])
		{
			if (map->map[row][col] == PLAYER_EA
				|| map->map[row][col] == PLAYER_NO
				|| map->map[row][col] == PLAYER_SO
				|| map->map[row][col] == PLAYER_WE)
			{
				*pos = ft_vector_init(col, row);
				*dir = ft_get_dir(map->map[row][col]);
			}
		}
	}
}

static t_vector_2d	ft_get_dir(e_map_elements player)
{
	t_vector_2d	dir;

	if (player == PLAYER_EA)
		dir = ft_vector_init(1, 0);
	else if (player == PLAYER_NO)
		dir = ft_vector_init(0, -1);
	else if (player == PLAYER_SO)
		dir = ft_vector_init(0, 1);
	else if (player == PLAYER_WE)
		dir = ft_vector_init(-1, 0);
	else
		dir = ft_vector_init(-1, -1);
	return (dir);
}
