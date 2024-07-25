/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 22:03:40 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/25 17:01:33 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_sprites(t_data *data, int sprite_count, int y, int x);

void	init_sprites(t_data *data)
{
	int	x;
	int	y;
	int	sprite_count;

	data->sprites = malloc(sizeof(t_sprite_data) * data->opponent_count);
	if (data->sprites == NULL)
	{
		ft_putendl_fd("Error\nMalloc failed", 2);
		exit(EXIT_FAILURE);
	}
	ft_memset(data->sprites, 0, sizeof(t_sprite_data) * data->opponent_count);
	y = -1;
	sprite_count = 0;
	while (data->map->map[++y])
	{
		x = -1;
		while (data->map->map[y][++x] != END)
		{
			if (data->map->map[y][x] == OPPONENT)
			{
				fill_sprites(data, sprite_count, y, x);
				sprite_count++;
			}
		}
	}
}

static void	fill_sprites(t_data *data, int sprite_count, int y, int x)
{
	data->sprites[sprite_count].pos = (t_vector_2d){y + 0.5, x + 0.5};
	data->sprites[sprite_count].dir = (t_vector_2d){1, 0};
	data->sprites[sprite_count].texture = 0;
	data->sprites[sprite_count].last_animation_change = 0;
	data->sprites[sprite_count].animation_speed = 0.2;
	data->sprites[sprite_count].move_speed = 0.02;
	data->sprites[sprite_count].last_idle = mlx_get_time();
	data->sprites[sprite_count].last_move = mlx_get_time();
	data->sprites[sprite_count].state = OPPONENT_IDLE;
}
