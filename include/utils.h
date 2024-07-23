/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:19:48 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/23 09:17:37 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void			ft_exit(void);

t_textures	determine_direction(const t_vector_2d ray_dir, const int side);
t_raycast_data	init_raycast_data(const t_data *data, const int x);
void			set_last_xpos(double xpos);
double calculate_distance(t_vector_2d point1, t_vector_2d point2);

#endif
