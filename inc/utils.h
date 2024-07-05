/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:19:48 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/02 19:19:52 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

void ft_exit();
t_direction	determine_direction(const t_vector_2d ray_dir, const int side);
t_raycast_data	init_raycast_data(const t_data *data, const int x);
void set_last_xpos(double xpos);

#endif
