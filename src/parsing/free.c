/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:21:14 by lzipp             #+#    #+#             */
/*   Updated: 2024/07/04 14:52:44 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
void	ft_free_textures(char ***textures)
{
	int	i;

	i = -1;
	while (++i < 5)
		free((*textures)[i]);
	free(*textures);
}

void	ft_free_rgb(int ***rgb)
{
	int		i;

	i = -1;
	while (++i < 2)
		free((*rgb)[i]);
	free(*rgb);
}
