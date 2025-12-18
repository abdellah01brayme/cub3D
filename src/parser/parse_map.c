/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:30:46 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/18 10:34:09 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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
		{
			print_error3("Invalid MAP charater in this line: ", line, "\n");
			return (-1);
		}
		if (ft_strchr("NSWE", s[*offset]))
			count++;
		if (s[*offset - 1] == '\n' && s[*offset] == '\n' && s[*offset + 1]
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
	if (!info->wall_imgs[NORTH])
		return (print_error2("Element not inserted: ", "NORTH"));
	if (!info->wall_imgs[SOUTH])
		return (print_error2("Element not inserted: ", "SOUTH"));
	if (!info->wall_imgs[EAST])
		return (print_error2("Element not inserted: ", "EAST"));
	if (!info->wall_imgs[WEST])
		return (print_error2("Element not inserted: ", "WEST"));
	return (0);
}

static void	set_player(t_info *info, int y, int x)
{
	info->player.x_pos = x * GRID_WIDTH + GRID_WIDTH / 2;
	info->player.y_pos = y * GRID_HIEGHT + GRID_HIEGHT / 2;
	info->player.x_step = 0;
	info->player.y_step = 0;
	if (info->map[y][x] == 'N')
	{
		info->player.y_step = -1;
		info->player.angle = 3 * PI / 2;
	}
	else if (info->map[y][x] == 'E')
	{
		info->player.x_step = 1;
		info->player.angle = 0;
	}
	else if (info->map[y][x] == 'S')
	{
		info->player.y_step = 1;
		info->player.angle = PI / 2;
	}
	else
	{
		info->player.x_step = -1;
		info->player.angle = PI;
	}
}

static void	find_player(t_info *info)
{
	int	y;
	int	x;

	y = 0;
	while (info->map[y])
	{
		x = 0;
		while (info->map[y][x])
		{
			if (ft_strchr("NSWE", info->map[y][x]))
			{
				set_player(info, y, x);
				info->map[y][x] = '0';
				break ;
			}
			x++;
		}
		y++;
	}
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
	find_player(info);
	return (0);
}
