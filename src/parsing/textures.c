/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:04:22 by lzipp             #+#    #+#             */
/*   Updated: 2024/06/19 16:04:47 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

bool ft_get_texture(char **line, char ***textures_ptr)
{
	char	*texture;
	char	direction[3];
	int		fd;	

	ft_memmove(direction, *line, 2);
	direction[2] = NULL;
	texture = ft_strtrim(*line + 2, " ");
	if (ft_check_texture(&texture) == false)
		return (false);
}

bool	ft_check_texture(char **texture)
{
	int	fd;

	if (ft_strrcmp(*texture, ".png", 4) != 0)
		return (perror("Error: texture must be of type .png"), false);
	fd = open(*texture, O_RDONLY);
	if (fd == -1)
		return (perror("Error: could not open texture"), false);
	close(fd);
	fd = open(*texture, O_DIRECTORY);
	if (fd != -1)
		return (perror("Error: texture must be a file"), false);
	return (close(fd), true);
}