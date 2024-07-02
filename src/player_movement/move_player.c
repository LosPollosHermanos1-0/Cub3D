/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:20:08 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/02 10:20:45 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vector_2d	generate_movement_vector(const t_data *data)
{
	const t_player		*p = data->player;
	const t_vector_2d	perp = ft_vector_perpendicular(p->dir);
	mlx_t				*mlx;
	t_vector_2d			movement;

	mlx = data->window->mlx;
	movement = ft_vector_init(0, 0);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		movement = ft_vector_add(movement, p->dir);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		movement = ft_vector_add(movement, ft_vector_scale(p->dir, -1));
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		movement = ft_vector_add(movement, ft_vector_scale(perp, -1));
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		movement = ft_vector_add(movement, perp);
	if ((mlx_is_key_down(mlx, MLX_KEY_W) || mlx_is_key_down(mlx, MLX_KEY_S))
		&& (mlx_is_key_down(mlx, MLX_KEY_A) || mlx_is_key_down(mlx, MLX_KEY_D)))
		movement = ft_vector_scale(movement, 0.7071);
	movement = ft_vector_scale(movement, p->move_speed);
	ft_print_vector(movement);
	return (movement);
}

void	move_player(const t_data *d)
{
	const t_vector_2d move = generate_movement_vector(d);
	const t_movement_check *check = check_move_with_wall_dist(move);

	if (check->can_move_x)
		printf("can move x\n");
	if (check->can_move_y)
		printf("can move y\n");
	if (check->can_move_x_and_y)
		printf("can move x and y\n");

	if (check->can_move_x && check->can_move_y && check->can_move_x_and_y)
		d->player->pos = ft_vector_add(d->player->pos, move);
	else if (check->can_move_x)
		d->player->pos.x += move.x;
	else if (check->can_move_y)
		d->player->pos.y += move.y;
}