/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:04:06 by mperrine          #+#    #+#             */
/*   Updated: 2025/12/15 16:05:04 by mperrine         ###   ########.fr       */
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

static void	parse_z(t_info **info, const char *s, t_vertex_info **vertex)
{
	char	**values;

	if (ft_strchr(s, ','))
	{
		values = ft_split(s, ',');
		(*vertex)->world.z = ft_atoi(values[0]);
		(*vertex)->col = (mlx_color){.rgba = hex_to_rgba(info, values[1] + 2)};
		free(values);
	}
	else
	{
		(*vertex)->world.z = ft_atoi(s);
		(*vertex)->col = (mlx_color){.rgba = 0xFFFFFFFF};
	}
}

static void	parse_line(t_info **info, const char *line, int line_nb)
{
	char	**coordinates;
	int		i;

	coordinates = ft_split(line, ' ');
	if (!coordinates)
		close_fdf(2, "Error: Line split failed", info);
	i = 0;
	while (coordinates[i])
		i++;
	(*info)->map[line_nb] = malloc(sizeof(t_vertex_info) * ((*info)->map_wdt + 1));
	if (!(*info)->map[line_nb])
		close_fdf(2, "Error: Malloc failed", info);
	(*info)->map[line_nb][(*info)->map_wdt] = NULL;
	i = 0;
	while (coordinates[i])
	{
		(*info)->map[line_nb][i]->world.x = i;
		(*info)->map[line_nb][i]->world.y = line_nb;
		parse_z(info, coordinates[i], &(*info)->map[line_nb][i]);
		i++;
	}
	free(coordinates);
}

static void	get_map_hgt(t_info **info, char *file)
{
	int		fd;
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
	(*info)->map_hgt = 0;
	while (line)
	{
		(*info)->map_hgt++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	parse_map(t_info **info, char *file)
{
	int		i;
	int		fd;
	char	*line;

	get_map_hgt(info, file);
	(*info)->map = malloc(sizeof(t_vertex_info *) * ((*info)->map_hgt + 1));
	if (!(*info)->map)
		close_fdf(2, "Error: Malloc failed", info);
	(*info)->map[(*info)->map_hgt] = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		close_fdf(1, NULL, info);
	i = -1;
	while (++i < (*info)->map_hgt)
	{
		line = get_next_line(fd);
		if (!line)
		{
			close(fd);
			close_fdf(1, "Error: Line is empty", info);
		}
		parse_line(info, line, i);
		free(line);
	}
	close(fd);
}
