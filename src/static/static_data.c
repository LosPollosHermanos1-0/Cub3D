/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmoritz <jmoritz@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:19:15 by jmoritz           #+#    #+#             */
/*   Updated: 2024/06/26 11:50:39 by jmoritz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

t_data *static_data()
{
    static t_data *data = NULL;

    if (data == NULL)
        data = init_data();
    return data;
}