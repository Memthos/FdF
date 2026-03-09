/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:04:06 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/09 16:42:49 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	parse_vertex(t_info **info, const char *s, int l_nb, int l_pos)
{
	char			**values;
	t_vinfo			*v;

	if (s[0] == '\n')
	{
		(*info)->map[l_nb][l_pos] = NULL;
		return (0);
	}
	v = malloc(sizeof(t_vinfo));
	if (!v)
		return (1);
	if (ft_strchr(s, ','))
	{
		values = ft_split(s, ',');
		if (!values)
			return (1);
		v->wp = (t_vector_3){l_pos, l_nb, ft_atoi(values[0])};
		free_tab(values);
	}
	else
		v->wp = (t_vector_3){l_pos, l_nb, ft_atoi(s)};
	v->col = (mlx_color){.rgba = 0xFFFFFFFF};
	(*info)->map[l_nb][l_pos] = v;
	return (0);
}

static int	parse_line(t_info **info, int fd, int line_nb)
{
	char	**coordinates;
	char	*line;
	int		i;
	int		ret;

	ret = 0;
	line = get_next_line(fd);
	coordinates = ft_split(line, ' ');
	if (line)
		free(line);
	i = 0;
	while (coordinates && coordinates[i])
		i++;
	(*info)->map[line_nb] = malloc(sizeof(t_vinfo *) * (i + 1));
	if (!(*info)->map[line_nb])
		ret = 1;
	if (!ret)
		(*info)->map[line_nb][i] = NULL;
	while (!ret && i-- > 0)
		ret = parse_vertex(info, coordinates[i], line_nb, i);
	free_tab(coordinates);
	return (ret);
}

static void	get_map_size(t_info **info, char *file)
{
	int		fd;
	char	*line;
	int		wdt;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		close_fdf(1, NULL, info);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		close_fdf(1, "Error: File is empty", info);
	}
	while (line)
	{
		(*info)->map_size.y++;
		wdt = 0;
		i = 0;
		while (line[i])
		{
			if (ft_isdigit(line[i++]))
			{
				while (line[i] && ft_isdigit(line[i]))
					i++;
				wdt++;
			}
		}
		if (wdt > (*info)->map_size.x)
			(*info)->map_size.x = wdt;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static void	read_file(int fd)
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
	int		ret;

	if (check_file_format(info, file))
		close_fdf(1, "Error: File type is wrong", info);
	ret = 0;
	(*info)->map_size = (t_vector_2){0, 0};
	get_map_size(info, file);
	(*info)->map = malloc(sizeof(t_vinfo **) * ((*info)->map_size.y + 1));
	if (!(*info)->map)
		close_fdf(2, "Error: Malloc failed", info);
	(*info)->map[(*info)->map_size.y] = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		close_fdf(1, NULL, info);
	i = 0;
	while (!ret && i < (*info)->map_size.y)
		ret = parse_line(info, fd, i++);
	read_file(fd);
	close(fd);
	if (ret)
		close_fdf(1, "Error: Parsing failed", info);
}
