/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:29:01 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/03 17:03:09 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	get_type(char *s, size_t i)
{
	if (s[i] == '\n')
		return (NEW_LINE);
	if (s[i] == 'N' && s[i + 1] == 'O')
		return (NORTH);
	if (s[i] == 'S' && s[i + 1] == 'O')
		return (SOUTH);
	if (s[i] == 'W' && s[i + 1] == 'E')
		return (WEST);
	if (s[i] == 'E' && s[i + 1] == 'A')
		return (EAST);
	if (s[i] == 'C')
		return (CEIL);
	if (s[i] == 'F')
		return (FLOOR);
	if (ft_strchr(" 10NSEW", s[i]))
		return (MAP);
	return (-1);
}

int	parser(t_info *info, char *file)
{
	size_t	offset;
	int		type;

	offset = 0;
	while (file[offset])
	{
		type = get_type(file, offset);
		if (type == NEW_LINE)
			++offset;
		else if (type < 0)
		{
			print_error3("unacceptable element: ", file + offset, "\n");
			return (1);
		}
		else if (parse_element(info, file, &offset, type))
			return (1);
	}
	if (!info->map)
		return (print_error2("Element not inserted: ", "MAP"));
	return (0);
}
