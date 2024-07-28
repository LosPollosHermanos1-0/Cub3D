/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:19:48 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/28 12:56:05 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

void			ft_exit(void);

t_textures		determine_direction(const t_vector_2d ray_dir, const int side);
t_raycast_data	init_raycast_data(const t_data *data, const int x);
void			set_last_xpos(double xpos);
double			calculate_distance(t_vector_2d point1, t_vector_2d point2);
static bool		ft_validate_opponents(char ***map_ptr);

#endif
