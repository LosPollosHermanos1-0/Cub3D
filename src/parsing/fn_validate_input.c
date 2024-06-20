/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_validate_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzipp <lzipp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:51:36 by lzipp             #+#    #+#             */
/*   Updated: 2024/06/20 13:53:39 by lzipp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/parsing.h"

bool fn_validate_input(int argc, char **argv)
{
	if (argc != 2)
		return(perror("Usage: ./cub3d <mapname.cub>"), false);
	if (ft_strlen(argv[1]) <= 4 || ft_strrchr(".cub", argv[1]) != 0)
		return(perror("Error: Incorrect number of arguments"), false);
	return (true);
}

// test
// #include "../../inc/parsing.h"
// int main(void)
// {
// 	char *c1[] = {"./cub3d", "mapname.cub"};
// 	char *c2[] = {"./cub3d", "a.cub"};
// 	char *w1[] = {"./cub3d"};
// 	char *w2[] = {"./cub3d", "mapname"};
// 	char *w3[] = {"./cub3d", "mapname.cu"};
// 	char *w4[] = {"./cub3d", "mapname.cub", "mapname2.cub"};

	
// }
