/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:29:01 by aid-bray          #+#    #+#             */
/*   Updated: 2025/11/29 18:31:55 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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

int	print_error(char *msg1)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg1, 2);
	write (1, "\n", 1);
	return (-1);
}

int	print_error2(char *msg1, char *msg2)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg1, 2);
	write (1, "'", 1);
	ft_putstr_fd(msg2, 2);
	write (1, "'\n", 2);
	return (-1);
}

int	print_error3(char *msg1, char *file, char *end)
{
	int	i;

	i = 0;
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg1, 2);
	write (1, "'", 1);
	while (file[i] && !ft_strchr(end, file[i]))
		write (1, &file[i++], 1);
	write (1, "'\n", 2);
	return (-1);
}

int	get_rgb_number(char *file, size_t *offset)
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

int	parse_color(int *color, char *file, size_t *offset)
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

int	parse_texture(t_info *info, char *file, size_t *offset, int type)
{
	char	*texture;
	void	*img;
	
	(*offset) += 2;
	if (file[*offset] != ' ')
	{
		print_error("Invalid path to texture");
		return (-1);
	}
	(*offset) += 1;
	texture = file + *offset;
	while (file[*offset] && file[*offset] != '\n')
		(*offset)++;
	file[*offset] = '\0';
	(*offset)++;
	img = mlx_xpm_file_to_image(info->mlx, texture, &info->texture_width[type],
		&info->texture_height[type]);
	if (!img) // && info->texture_width[type] != 0 if the texture is empty
		return (print_error2("Invalide texture path: ", texture - 3));
	info->texture_paths[type] = img;
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
	else if(type == CEIL)
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

void print_info(t_info *info)
{
    printf("***********start*****************\n");
	printf("*textures:\n");
		printf("====%s\n", (char*)info->texture_paths[0]);

	printf("*NORTH: %s\n*SOUTH: %s\n* WEST: %s\n* EAST: %s\n", (char *)info->texture_paths[NORTH],
			(char *)info->texture_paths[SOUTH],
			(char *)info->texture_paths[WEST],
			(char *)info->texture_paths[EAST]);
	printf("*----------------------------------------\n");
	printf("*FLOOR: %d\n", info->color_floor);
	printf("* CEIL: %d\n", info->color_ceil);
	printf("*----------------------------------------\n");
	printf("*MAP:\n");
	int i = 0;
	while (info->map[i])
	{
		printf("*%s\n", info->map[i]);
		i++;
	}
	printf("***********END*****************\n");
}