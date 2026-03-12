/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 09:57:01 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/12 16:01:30 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static long	coords_by_line(char *line)
{
	long	size;
	int		i;

	i = 0;
	size = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			while (line[i] && ft_isdigit(line[i]))
				i++;
			size++;
		}
		if (line[i])
			i++;
	}
	return (size);
}

int	check_map(t_info **info, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		close_fdf(1, NULL, *info);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (1);
	}
	(*info)->map_size.x = coords_by_line(line);
	while (line)
	{
		(*info)->map_size.y++;
		if (coords_by_line(line) != (*info)->map_size.x)
			return (1);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	check_file_format(t_info **info, char *file)
{
	char	**file_parts;
	long	i;
	size_t	len;
	int		ret;

	file_parts = ft_split(file, '.');
	if (!file_parts)
		close_fdf(1, "Error: Filename split failed", *info);
	ret = 1;
	i = 0;
	while (file_parts[i])
		i++;
	len = ft_strlen(file_parts[i - 1]);
	if (len < 3)
		return (1);
	if (file_parts[i - 1][len - 1] == 'f' && file_parts[i - 1][len - 2] == 'd'
		&& file_parts[i - 1][len - 3] == 'f')
		ret = 0;
	free_tab(file_parts);
	return (ret);
}
