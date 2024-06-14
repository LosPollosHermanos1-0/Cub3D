/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_validate_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:51:36 by lzipp             #+#    #+#             */
/*   Updated: 2024/06/14 12:33:35 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/cub3d.h"

bool fn_validate_input(int argc, char **argv)
{
	if (argc != 2)
		return(perror("Usage: ./cub3d <mapname.cub>"), false);
	if (ft_strlen(argv[1]) <= 4 || ft_strrchr(".cub", argv[1]) != 0)6
		return(perror("Error: Incorrect number of arguments"), false);
	return (true);
}
