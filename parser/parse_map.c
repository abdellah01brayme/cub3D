/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:16:43 by aid-bray          #+#    #+#             */
/*   Updated: 2025/11/12 13:40:54 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static int	first_check_map(char *s, size_t *offset)
{
	char	*line;
	int		count;

	line = s;
	count = 0;
	while (s[*offset])
	{
		if (s[*offset] == '\n')
			line = s + *offset + 1;
		if (!ft_strchr(" 01\nNSWE", s[*offset]))
			return (print_error3("Invalid MAP charater in this line: ", line, "\n"));
		if (ft_strchr("NSWE", s[*offset]))
			count++;
		if (s[*offset - 1] == '\n'&& s[*offset] == '\n' && s[*offset + 1]
			&& s[*offset + 1] != '\n')
			return (print_error2("Invalid MAP: ", "empty line in the map"));
		(*offset)++;
	}
	if (count != 1)
		return (print_error2("Invalid MAP: ", "number of player positions"));
	return (0);
}

static int	is_inserted(t_info *info)
{
	if (info->color_ceil < 0)
		return (print_error2("Element not inserted: ", "CEIL"));
	if (info->color_floor < 0)
		return (print_error2("Element not inserted: ", "FLOOR"));
	if (!info->texture_paths[NORTH])
		return (print_error2("Element not inserted: ", "NORTH"));
	if (!info->texture_paths[SOUTH])
		return (print_error2("Element not inserted: ", "SOUTH"));
	if (!info->texture_paths[EAST])
		return (print_error2("Element not inserted: ", "EAST"));
	if (!info->texture_paths[WEST])
		return (print_error2("Element not inserted: ", "WEST"));
	return (0);
}

int	parse_map(t_info *info, char *file, size_t *offset)
{
	size_t	i;

	i = *offset;
	if (is_inserted(info))
		return (ft_putstr_fd("must insert the element befor the MAP\n", 2), 1);
	if (first_check_map(file, offset))
		return (1);
	info->map = ft_split(file + i, '\n');
	if (!info->map)
		return (print_error(strerror(errno)));
	if (check_map(info->map))
		return (1);
	return (0);
}
