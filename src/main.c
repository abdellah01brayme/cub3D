/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:28:34 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/19 17:16:24 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int ac, char **av)
{
	t_map	map;

	if (ac != 2)
		return (print_error2("Invalide arguments: ", "./cub3D path_to_file"));
	initial_info(&map);
	if (parser(&map, av[1]))
	{
		destroy_info(&map);
		return (1);
	}
	if (initial_other(&map))
	{
		destroy_info(&map);
		return (1);
	}
	creat_window(&map);
	return (0);
}
