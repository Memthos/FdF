/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:04:06 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/12 15:58:02 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static uint32_t	parse_color(char *value)
{
	uint32_t	color;
	int			i;

	if (ft_strlen(value) != 8)
		return (0);
	i = 2;
	color = 0;
	while (value[i])
	{
		if (ft_isdigit(value[i]))
			color = (color * 16) + (value[i++] - '0');
		else if (value[i] >= 'a' && value[i] <= 'z')
			color = (color * 16) + (value[i++] - 'a' + 10);
		else if (value[i] >= 'A' && value[i] <= 'Z')
			color = (color * 16) + (value[i++] - 'A' + 10);
		else
			return (0);
	}
	color = (color << 8) | 0xFF;
	return (color);
}

static int	parse_vertex(t_info **info, const char *s, int hgt, int wdt)
{
	char			**values;
	t_vinfo			*vertex;
	uint32_t		color;

	vertex = malloc(sizeof(t_vinfo));
	if (!vertex)
		return (1);
	color = 0x000000FF;
	if (ft_strchr(s, ','))
	{
		values = ft_split(s, ',');
		if (!values)
			return (1);
		vertex->wp = (t_vector_3){wdt, hgt, ft_atoi(values[0])};
		color = parse_color(values[1]);
		free_tab(values);
	}
	else
		vertex->wp = (t_vector_3){wdt, hgt, ft_atoi(s)};
	if (!color)
		return (1);
	vertex->col = (mlx_color){.rgba = color};
	(*info)->map[hgt][wdt] = vertex;
	return (0);
}

static int	parse_line(t_info **info, int fd, int hgt)
{
	char	**coordinates;
	char	*line;
	int		wdt;
	int		ret;

	ret = 0;
	line = get_next_line(fd);
	coordinates = ft_split(line, ' ');
	if (line)
		free(line);
	wdt = 0;
	while (coordinates && coordinates[wdt])
		wdt++;
	(*info)->map[hgt] = malloc(sizeof(t_vinfo *) * (wdt + 1));
	if (!(*info)->map[hgt])
		ret = 1;
	if (!ret)
		(*info)->map[hgt][wdt] = NULL;
	while (!ret && wdt-- > 0)
		ret = parse_vertex(info, coordinates[wdt], hgt, wdt);
	free_tab(coordinates);
	return (ret);
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
	int		hgt;
	int		fd;
	int		ret;

	(*info)->map_size = (t_vector_2){0, 0};
	if (check_file_format(info, file) || check_map(info, file))
		close_fdf(1, "Error: File is wrong", *info);
	ret = 0;
	(*info)->map = malloc(sizeof(t_vinfo **) * ((*info)->map_size.y + 1));
	if (!(*info)->map)
		close_fdf(2, "Error: Malloc failed", *info);
	(*info)->map[(*info)->map_size.y] = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		close_fdf(1, NULL, *info);
	hgt = 0;
	while (!ret && hgt < (*info)->map_size.y)
		ret = parse_line(info, fd, hgt++);
	read_file(fd);
	close(fd);
	if (ret)
		close_fdf(1, "Error: Parsing failed", *info);
}
