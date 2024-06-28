/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:04:22 by lzipp             #+#    #+#             */
/*   Updated: 2024/06/28 14:39:34 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

bool	ft_get_texture(char **line, char ***texture_ptr)
{
	char	*texture;
	char	direction[3];
	int		index;

	ft_memmove(direction, *line, 2);
	direction[2] = '\0';
	texture = ft_strtrim(*line + 2, " ");
	if (ft_check_texture(&texture) == false)
		return (false);
	if (ft_strcmp(direction, "NO") == 0)
		index = 0;
	else if (ft_strcmp(direction, "SO") == 0)
		index = 1;
	else if (ft_strcmp(direction, "WE") == 0)
		index = 2;
	else if (ft_strcmp(direction, "EA") == 0)
		index = 3;
	else
		return (perror("Error: invalid texture direction"), false);
	if ((*texture_ptr)[index])
		return (perror("Error: Same direction encountered twice"), false);
	(*texture_ptr)[index] = texture;
	return (true);
}

bool	ft_check_texture(char **texture)
{
	int	fd;

	if (!*texture)
		return (perror("Error: texture could not be read."), false);
	if (ft_strrncmp(*texture, ".png", 4) != 0)
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
