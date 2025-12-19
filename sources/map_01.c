/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:04:06 by mperrine          #+#    #+#             */
/*   Updated: 2025/12/19 13:37:14 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

static int	parse_vertex(t_info **info, const char *s, int l_nb, int l_pos)
{
	char			**values;
	t_vertex_info	*v;
	u_int32_t		rgba;

	v = malloc(sizeof(t_vertex_info));
	if (!v)
		return (1);
	rgba = 0xFFFFFFFF;
	if (ft_strchr(s, ','))
	{
		values = ft_split(s, ',');
		if (!values)
			return (1);
		v->wp = (t_vector_3){l_pos, l_nb, ft_atoi(values[0])};
		rgba = hex_to_rgba(values[1] + 2);
		free_tab(values);
		if (!rgba)
			return (1);
	}
	else
		v->wp = (t_vector_3){l_pos, l_nb, ft_atoi(s)};
	v->col = (mlx_color){.rgba = rgba};
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
		ret = 1;
	if (!ret)
		(*info)->map[line_nb][i] = NULL;
	while (!ret && i-- > 0)
		ret = parse_vertex(info, coordinates[i], line_nb, i);
	free_tab(coordinates);
	return (ret);
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
	int		ret;

	if (check_file_format(info, file))
		close_fdf(1, "Error: File type is wrong", info);
	ret = 0;
	hgt = get_map_hgt(info, file);
	(*info)->map = malloc(sizeof(t_vertex_info **) * (hgt + 1));
	if (!(*info)->map)
		close_fdf(2, "Error: Malloc failed", info);
	(*info)->map[hgt] = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		close_fdf(1, NULL, info);
	i = -1;
	while (!ret && ++i < hgt)
		ret = parse_line(info, fd, i);
	read_file(fd);
	close(fd);
	if (ret)
		close_fdf(1, "Error: Parsing failed", info);
}
