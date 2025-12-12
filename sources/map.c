/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:04:06 by mperrine          #+#    #+#             */
/*   Updated: 2025/12/12 14:10:36 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

static void	get_map_size(t_info **info, char *file)
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
	(*info)->map_wdt = (int)ft_strlen(line);
	(*info)->map_hgt = 0;
	while (line)
	{
		(*info)->map_hgt++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static void	parse_line(t_info **info, int fd, int line_nb)
{
	char	*line;
	char	**coordinates;
	char	**cur_coord;
	int		i;

	line = get_next_line(fd);
	if (!line)
		close_fdf(1, "Error: Line is empty", info);
	coordinates = ft_split(line, ' ');
	if (!coordinates)
		close_fdf(2, "Error: Line split failed", info);
	i = -1;
	cur_coord = NULL;
	while (coordinates[i++])
	{
		if (ft_strchr(coordinates[i], ','))
			cur_coord = ft_split(coordinates[i], ',');
		if (!cur_coord)
			(*info)->map[line_nb][i].col = (mlx_color){.rgba = 0xFFFFFFFF};
		else
			(*info)->map[line_nb][i].col = (mlx_color){.rgba = 0x4287F5FF};
		(*info)->map[line_nb][i].world.x = i;
		(*info)->map[line_nb][i].world.y = line_nb;
		(*info)->map[line_nb][i].world.z = ft_atoi(coordinates[i]);
	}
}

void	parse_map(t_info **info, char *file)
{
	int	i;
	int	fd;

	get_map_size(info, file);
	(*info)->map = malloc(sizeof(t_vertex_info *) * (*info)->map_hgt);
	if (!(*info)->map)
		close_fdf(2, "Error: Malloc failed", info);
	i = -1;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		close_fdf(1, NULL, info);
	while (i++ < (*info)->map_hgt)
	{
		(*info)->map[i] = malloc(sizeof(t_vertex_info) * (*info)->map_wdt);
		if (!(*info)->map[i])
			close_fdf(2, "Error: Malloc failed", info);
		parse_line(info, fd, i);
	}
	close(fd);
}

void	world_to_screen(t_vertex_info *vertex, t_vector_3 *world)
{
	vertex->pos.x = (world->x - world->y) * TILE_SIZE_X / 2;
	vertex->pos.y = (world->x + world->y) * TILE_SIZE_Y / 2 - world->z;
}
