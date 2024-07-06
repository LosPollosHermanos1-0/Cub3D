/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:19:15 by jmoritz           #+#    #+#             */
/*   Updated: 2024/07/05 10:35:58 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

t_data *static_data()
{
	static t_data data;

	return &data;
}

