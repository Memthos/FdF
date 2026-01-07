/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 08:59:27 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/07 15:04:41 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void    isometric_projection(t_info **info)
{
	int          l_nb;
	int          l_pos;
	t_vector_2   half;

	half = (t_vector_2){(*info)->tile_size.x / 2, (*info)->tile_size.y / 2};

	l_nb = -1;
	while ((*info)->map[++l_nb])
	{
		l_pos = -1;
		while ((*info)->map[l_nb][++l_pos])
		{
			(*info)->map[l_nb][l_pos]->sp.x = ((*info)->map[l_nb][l_pos]->wp.x
				+ (*info)->map[l_nb][l_pos]->wp.y) * half.x;

			(*info)->map[l_nb][l_pos]->sp.y = ((*info)->map[l_nb][l_pos]->wp.y
				- (*info)->map[l_nb][l_pos]->wp.x) * half.y
				- (*info)->map[l_nb][l_pos]->wp.z * half.y * SCALE_Z
				+ (*info)->map_z.y * half.y * SCALE_Z
				+ ((*info)->map_size.x - 1) * half.y;
		}
	}
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
	int		ret;

	file_parts = ft_split(file, '.');
	if (!file_parts)
		close_fdf(1, "Error: Filename split failed", info);
	ret = 1;
	i = 0;
	while (file_parts[i])
		i++;
	len = (int) ft_strlen(file_parts[i - 1]);
	if (file_parts[i - 1][len - 1] == 'f' && file_parts[i - 1][len - 2] == 'd'
		&& file_parts[i - 1][len - 3] == 'f')
		ret = 0;
	free_tab(file_parts);
	return (ret);
}

static void	get_map_size(t_info **info)
{
	int	l_pos;

	(*info)->map_size = (t_vector_2){0, 0};
	(*info)->map_z = (t_vector_2){0, 0};
	while ((*info)->map[(*info)->map_size.y])
	{
		l_pos = 0;
		while ((*info)->map[(*info)->map_size.y][l_pos])
		{
			if ((*info)->map[(*info)->map_size.y][l_pos]->wp.z
					< (*info)->map_z.x)
				(*info)->map_z.x
					= (*info)->map[(*info)->map_size.y][l_pos]->wp.z;
			if ((*info)->map[(*info)->map_size.y][l_pos]->wp.z
					> (*info)->map_z.y)
				(*info)->map_z.y
					= (*info)->map[(*info)->map_size.y][l_pos]->wp.z;
			l_pos++;
		}
		if (l_pos - 1 > (*info)->map_size.x)
			(*info)->map_size.x = l_pos - 1;
		(*info)->map_size.y++;
	}
}

void    set_sizes(t_info **info)
{
	int    tiles_w;
	int    tiles_h;
	int    x_range;
	int    y_range;

	get_map_size(info);
	x_range = (*info)->map_size.x + (*info)->map_size.y - 1;
	y_range = (*info)->map_size.x + (*info)->map_size.y - 2
			+ ((*info)->map_z.y - (*info)->map_z.x) * SCALE_Z;
	tiles_w = (SCREEN_W * 2) / x_range;
	tiles_h = (SCREEN_H * 2) / y_range;
	if (tiles_w < tiles_h)
		(*info)->tile_size.x = tiles_w;
	else
		(*info)->tile_size.x = tiles_h;
	(*info)->tile_size.y = (*info)->tile_size.x / 2;
	(*info)->sc_size.x = x_range * (*info)->tile_size.y;
	(*info)->sc_size.y = y_range * (*info)->tile_size.y;
}