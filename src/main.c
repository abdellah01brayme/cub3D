/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:28:34 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/19 15:35:13 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 2)
		return (print_error2("Invalide arguments: ", "./cub3D path_to_file"));
	initial_info(&info);
	if (parser(&info, av[1]))
	{
		destroy_info(&info);
		return (1);
	}
	if (initial_other(&info) || start_game(&info))
	{
		destroy_info(&info);
		return (1);
	}
	
	destroy_info(&info);
	return (0);
}
