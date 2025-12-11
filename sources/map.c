/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:04:06 by mperrine          #+#    #+#             */
/*   Updated: 2025/12/11 14:03:23 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

static int	get_nb_line(char *file)
{
	int		fd;
	int		nb;
	char	*line;

	nb = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (nb);
	line = get_next_line(fd);
	while (line)
	{
		nb++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (nb);
}

t_vertex_info	**parse_map(char *file)
{
	t_vertex_info	**map;
	int				lines;

	lines = get_nb_line(file);
	if (!lines)
		return (NULL);
	map = malloc(sizeof(t_vertex_info *) * (lines + 1));
	if (!map)
		return (NULL);
	return (map);
}