/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 11:21:43 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/20 15:37:53 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	get_rgb_number(char *file, size_t *offset)
{
	int		rgb;

	rgb = 0;
	if (!ft_isdigit(file[*offset]))
		return (-1);
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
	i = 0;
	while (i < 3)
	{
		skip_space(file, offset);
		n[i] = get_rgb_number(file, offset);
		if (n[i] < 0)
			return (print_error3("Invalid RGB range: ", line, "\n"));
		skip_space(file, offset);
		if ((i < 2 && file[*offset] != ','))
			return (print_error3("Invalid RGB format: ", line, "\n"));
		if (i < 2 && file[*offset] == ',')
			(*offset)++;
		i++;
	}
	if (file[*offset] != '\n' && file[*offset])
		return (print_error3("Invalid RGB format: ", line, "\n"));
	*color = n[0] << 16 | n[1] << 8 | n[2];
	return (*color);
}

static int	parse_texture(t_map *info, char *file, size_t *offset, int type)
{
	t_textur	*textur;
	char		*path;
	size_t		i;

	textur = &info->textures[type];
	path = file + *offset;
	(*offset) += 2;
	if (file[*offset] != ' ')
		return (print_error3("Invalid texture format: ", path, "\n"));
	skip_space(file, offset);
	path = file + *offset;
	while (file[*offset] && file[*offset] != '\n')
		(*offset)++;
	i = *offset - 1;
	while (file[i] == ' ')
		file[i--] = '\0';
	file[*offset] = '\0';
	(*offset)++;
	textur->img = mlx_xpm_file_to_image(info->mlx, path, &textur->textur_width,
			&textur->textur_height);
	if (!textur->img)
		return (print_error2("can't load texture: ", path));
	textur->addr = mlx_get_data_addr(textur->img, &textur->bits_per_pxl,
			&textur->length_line, &textur->endian);
	return (0);
}

int	parse_element(t_map *info, char *file, size_t *offset, int type)
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
		if (info->textures[type].img)
			return (print_error2("duplication of element: ", "TEXTURE"));
		if (parse_texture(info, file, offset, type))
			return (1);
	}
	else if (type == MAP)
		if (parse_map(info, file, offset))
			return (1);
	return (0);
}
