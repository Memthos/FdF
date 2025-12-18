/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 08:59:27 by mperrine          #+#    #+#             */
/*   Updated: 2025/12/18 10:23:30 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

t_vector_2	world_to_screen(t_vertex_info *v)
{
	t_vector_2	screen;

	screen.x = (v->wp.x - v->wp.y) * TILE_SIZE_X / 2;
	screen.y = (v->wp.x + v->wp.y) * TILE_SIZE_Y / 2 - v->wp.z;
	return (screen);
}

uint32_t	hex_to_rgba(const char *hex)
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
			return (0);
		rgba <<= 4 | nb;
		i++;
	}
	return (rgba);
}

int	check_file_format(t_info **info, char *file)
{
	char	**file_parts;
	int		i;
	int		len;

	file_parts = ft_split(file, '.');
	if (!file_parts)
		close_fdf(1, "Error: Filename split failed", info);
	i = 0;
	while (file_parts[i])
		i++;
	len = ft_strlen(file_parts[i - 1]);
	if (file_parts[i - 1][len - 1] == 'f' && file_parts[i - 1][len - 2] == 'd'
		&& file_parts[i - 1][len - 3] == 'f')
		return (0);
	return (1);
}
