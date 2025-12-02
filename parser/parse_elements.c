/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:21:43 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/01 18:43:33 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	get_rgb_number(char *file, size_t *offset)
{
	int		rgb;

	rgb = 0;
	while (ft_isdigit(file[*offset]))
	{
		rgb = rgb * 10 + file[*offset] - '0';
		if (rgb > 255)
			return (-1);
		(*offset)++;
	}
	return (rgb);
}

static int	parse_color(int *color, char *file, size_t *offset)
{
	int		n[3];
	int		i;
	char	*line;

	line = file + *offset;
	if (file[++(*offset)] != ' ')
		return (print_error3("Invalid RGB format: ", line, "\n"));
	(*offset)++;
	i = 0;
	while (i < 3)
	{
		n[i] = get_rgb_number(file, offset);
		if (n[i] < 0)
			return (print_error3("Invalid RGB range: ", line, "\n"));
		if (i < 2 && file[*offset] != ',')
			return (print_error3("Invalid RGB format: ", line, "\n"));
		if (file[*offset] == ',')
			(*offset)++;
		i++;
	}
	if (file[*offset] != '\n' && file[*offset])
		return (print_error3("Invalid RGB format: ", line, "\n"));
	*color = n[0] << 16 | n[1] << 8 | n[2];
	return (*color);
}

static int	parse_texture(t_info *info, char *file, size_t *offset, int type)
{
	char	*texture;
	void	*img;

	(*offset) += 2;
	if (file[*offset] != ' ')
	{
		print_error("Invalid texture path");
		return (-1);
	}
	(*offset) += 1;
	texture = file + *offset;
	while (file[*offset] && file[*offset] != '\n')
		(*offset)++;
	file[*offset] = '\0';
	(*offset)++;
	img = mlx_xpm_file_to_image(info->mlx, texture, &info->wall_width[type],
			&info->wall_height[type]);
	if (!img) // && info->wall_width[type] != 0 if the texture is empty
		return (print_error2("Invalide texture: ", texture - 3));
	info->wall_imgs[type] = img;
	return (0);
}

int	parse_element(t_info *info, char *file, size_t *offset, int type)
{
	if (type == FLOOR)
	{
		if (info->color_floor >= 0)
			return (print_error2("duplication of element: ", "FLOOR"));
		if (parse_color(&info->color_floor, file, offset) < 0)
			return (1);
	}
	else if (type == CEIL)
	{
		if (info->color_ceil >= 0)
			return (print_error2("duplication of element: ", "CEIL"));
		if (parse_color(&info->color_ceil, file, offset) < 0)
			return (1);
	}
	else if (type == NORTH || type == SOUTH || type == WEST || type == EAST)
	{
		if (parse_texture(info, file, offset, type))
			return (1);
	}
	else if (type == MAP)
	{
		if (parse_map(info, file, offset))
			return (1);
	}
	return (0);
}
