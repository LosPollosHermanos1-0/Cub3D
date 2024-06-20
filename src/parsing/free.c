/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:21:14 by lzipp             #+#    #+#             */
/*   Updated: 2024/06/20 14:21:40 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"
void	free_textures(char ***textures)
{
	int	i;

	i = -1;
	while (++i < 5)
		free((*textures)[i]);
	free(*textures);
}

void	free_map(char ***map)
{
	int	i;

	i = -1;
	while ((*map)[++i])
		free((*map)[i]);
	free(*map);
}
