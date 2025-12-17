/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:04:06 by mperrine          #+#    #+#             */
/*   Updated: 2025/12/17 13:52:40 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

static uint32_t	hex_to_rgba(t_info **info, const char *hex)
{
	uint32_t	rgba;
	uint32_t	nb;
	int			i;

	rgba = 0;
	i = 0;
	while (i < 8)
	{
		if (hex[i] >= '0' && hex[i] <= '9')
			nb = hex[i] - '0';
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			nb = hex[i] - 'a' + 10;
		else if (hex[i] >= 'A' && hex[i] <= 'F')
			nb = hex[i] - 'A' + 10;
		else
			close_fdf(1, "Map color error", info);
		rgba <<= 4 | nb;
		i++;
	}
	return (rgba);
}

static int	parse_vertex(t_info **info, const char *s, int line_nb, int line_pos)
{
	char			**values;
	t_vertex_info	*v;

	v = malloc(sizeof(t_vertex_info));
	if (!v)
		return (1);
	v->wp.x = line_pos;
	v->wp.y = line_nb;
	if (ft_strchr(s, ','))
	{
		values = ft_split(s, ',');
		if (!values)
			return (1);
		v->wp.z = ft_atoi(values[0]);
		v->col = (mlx_color){.rgba = hex_to_rgba(info, values[1] + 2)};
		free(values);
	}
	else
	{
		v->wp.z = ft_atoi(s);
		v->col = (mlx_color){.rgba = 0xFFFFFFFF};
	}
	v->sp = world_to_screen(v);
	(*info)->map[line_nb][line_pos] = v;
	return (0);
}

static int	parse_line(t_info **info, int fd, int line_nb)
{
	char	**coordinates;
	char	*line;
	int		i;

	line = get_next_line(fd);
	if (!line)
		return (1);
	coordinates = ft_split(line, ' ');
	free(line);
	if (!coordinates)
		return (1);
	i = 0;
	while (coordinates[i])
		i++;
	(*info)->map[line_nb] = malloc(sizeof(t_vertex_info *) * (i + 1));
	if (!(*info)->map[line_nb])
	{
		free(coordinates);
		return (1);
	}
	(*info)->map[line_nb][i] = NULL;
	while (coordinates[--i])
	{
		if (parse_vertex(info, coordinates[i], line_nb, i))
		{
			free(coordinates);
			return (1);
		}
	}
	free(coordinates);
	return (0);
}

static int	get_map_hgt(t_info **info, char *file)
{
	int		fd;
	int		hgt;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		close_fdf(1, NULL, info);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		close_fdf(1, "Error: File is empty", info);
	}
	hgt = 0;
	while (line)
	{
		hgt++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (hgt);
}

void	read_file(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

void	parse_map(t_info **info, char *file)
{
	int		i;
	int		fd;
	int		hgt;

	hgt = get_map_hgt(info, file);
	(*info)->map = malloc(sizeof(t_vertex_info **) * (hgt + 1));
	if (!(*info)->map)
		close_fdf(2, "Error: Malloc failed", info);
	(*info)->map[hgt] = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		close_fdf(1, NULL, info);
	i = -1;
	while (++i < hgt)
	{
		if (parse_line(info, fd, i))
		{
			read_file(fd);
			close(fd);
			close_fdf(1, "Error: Parsing failed", info);
		}
	}
	close(fd);
}
