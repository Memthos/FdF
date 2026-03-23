/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:04:06 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/23 15:31:34 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

static uint32_t	parse_color(char *value)
{
	uint32_t	color;
	int			i;

	if (ft_strlen(value) != 8 && !ft_isspace(value[ft_strlen(value) - 1]))
		return (0);
	i = 2;
	color = 0;
	while (value[i])
	{
		if (ft_isdigit(value[i]))
			color = (color * 16) + (value[i] - '0');
		else if (value[i] >= 'a' && value[i] <= 'z')
			color = (color * 16) + (value[i] - 'a' + 10);
		else if (value[i] >= 'A' && value[i] <= 'Z')
			color = (color * 16) + (value[i] - 'A' + 10);
		i++;
	}
	color = (color << 8) | 0xFF;
	return (color);
}

static int	parse_vertex(t_vinfo *vertex, const char *s, long hgt, long wdt)
{
	char			**values;
	uint32_t		color;

	color = 0xFFFFFFFF;
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
	vertex->sp = (t_vector_2){0, 0};
	return (0);
}

static int	parse_line(t_info *info, int fd, long hgt)
{
	char	**coordinates;
	char	*line;
	long	wdt;
	int		ret;

	ret = 0;
	line = get_next_line(fd);
	if (!line)
		return (1);
	coordinates = ft_split(line, ' ');
	free(line);
	if (!coordinates)
		return (1);
	info->map[hgt] = malloc(sizeof(t_vinfo) * info->map_size.x);
	if (!info->map[hgt])
		ret = 1;
	wdt = 0;
	while (!ret && wdt < info->map_size.x)
	{
		ret = parse_vertex(&info->map[hgt][wdt], coordinates[wdt], hgt, wdt);
		wdt++;
	}
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

void	parse_map(t_info *info, char *file)
{
	long	hgt;
	int		fd;
	int		ret;

	info->map_size = (t_vector_2){0, 0};
	if (check_file_format(info, file) || check_map(info, file))
		close_fdf(1, "Error: File is wrong", info);
	ret = 0;
	info->map = malloc(sizeof(t_vinfo *) * info->map_size.y);
	if (!info->map)
		close_fdf(2, "Error: Malloc failed", info);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		close_fdf(1, NULL, info);
	hgt = 0;
	while (!ret && hgt < info->map_size.y)
		ret = parse_line(info, fd, hgt++);
	read_file(fd);
	close(fd);
	if (ret)
	{
		clear_map(info, hgt);
		close_fdf(1, "Error: Parsing failed", info);
	}
}
