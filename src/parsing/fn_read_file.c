/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 08:39:57 by vscode            #+#    #+#             */
/*   Updated: 2024/06/19 08:54:54 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

bool fn_read_file(char *file_path, char ***textures, char ***map, int **colors)
{
	int			fd;
	char		*line;
	
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return(perror("Error: could not open file"), false);
	line = ft_get_next_line(fd);
	while
	// map is always last
}
