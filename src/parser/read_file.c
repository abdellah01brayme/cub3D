/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aid-bray <aid-bray@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 09:36:24 by aid-bray          #+#    #+#             */
/*   Updated: 2025/12/20 15:25:40 by aid-bray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#define SIZE_BUFFER 50

static char	*join(char *s1, char *s2)
{
	char	*new;

	if (!s1)
	{
		new = ft_strjoin("", s2);
	}
	else
	{
		new = ft_strjoin(s1, s2);
		free(s1);
	}
	if (!new && errno == ENOMEM)
		print_error2("when reading file: ", strerror(errno));
	return (new);
}

static char	*ft_read(int fd)
{
	char	buf[SIZE_BUFFER + 1];
	char	*file;
	int		lenght;

	file = NULL;
	while (1)
	{
		lenght = read (fd, buf, SIZE_BUFFER);
		if (lenght <= 0)
			break ;
		buf[lenght] = '\0';
		file = join(file, buf);
		if (!file)
			break ;
	}
	return (file);
}

static int	check_path(char *path)
{
	char	*tmp;
	int		len_path;
	int		i;

	len_path = ft_strlen(path);
	if (len_path <= 4)
		return (1);
	i = ft_strlen(".cub");
	tmp = ft_strrchr(path, '/');
	if (tmp && ft_strlen(tmp) <= 5)
		return (1);
	else if (!ft_strncmp(path + (len_path - i), ".cub", i))
		return (0);
	return (1);
}

char	*read_file(char *map_path)
{
	char	*file;
	int		fd;

	if (check_path(map_path))
	{
		print_error2("Invalide path: ", map_path);
		exit(1);
	}
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
	{
		print_error2(strerror(errno), map_path);
		close(fd);
		exit(1);
	}
	file = ft_read(fd);
	close(fd);
	if (!file)
		exit(1);
	return (file);
}
