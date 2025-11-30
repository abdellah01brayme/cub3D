/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 13:39:21 by aid-bray          #+#    #+#             */
/*   Updated: 2025/11/30 11:28:34 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	len_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

static int	check_closed(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ')
		{
			print_error2("Invalid MAP: unclosed line: ", line);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_round(char **map, int i, int j, int len_line)
{
	int	len_befor;
	int	len_after;

	if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ' || !map[i][j + 1])
		return (1);
	len_befor = ft_strlen(map[i - 1]);
	if (j >= len_befor)
		return (1);
	else if (map[i - 1][j] == ' ')
		return (1);
	len_after = ft_strlen(map[i + 1]);
	if (j >= len_after)
		return (1);
	else if (map[i + 1][j] == ' ')
		return (1);
	return (0);
}

static int	check_line(char **map, int i, int size_map, int len_line)
{
	int	j;

	j = 1;
	if (map[i][0] != '1' && map[i][0] != ' ')
		return (1);
	while (map[i][j])
	{
		if (map[i][j] == '0' && !map[i][j + 1])
			return (1);
		if (map[i][j] == '0' && check_round(map, i, j, len_line))
			return (1);
		if (ft_strchr("WESN", map[i][j]) && check_round(map, i, j, len_line))
			return (1);
		j++;
	}
	return (0);
}

int	check_map(char **map)
{
	int	size;
	int	i;
	int	len;

	i = 1;
	size = len_map(map);
	if (check_closed(map[0]) || check_closed(map[size - 1]))
		return (1);
	while (map[i + 1])
	{
		len = ft_strlen(map[i]);
		if (check_line(map, i, size, len))
			return (print_error2("Invalid MAP: unclosed line: ", map[i]));
		i++;
	}
	return (0);
}
