/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 08:59:27 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/11 17:45:37 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	isometric_projection(t_info **info)
{
	int	hgt;
	int	wdt;
	int	hgt_offset;

	if ((*info)->map_size.x > (*info)->map_size.y)
		hgt_offset = ((*info)->map_size.x - (*info)->map_size.y);
	else
		hgt_offset = (*info)->map_size.y - (*info)->map_size.x;
	hgt = 0;
	while ((*info)->map[hgt])
	{
		wdt = 0;
		while ((*info)->map[hgt][wdt])
		{
			(*info)->map[hgt][wdt]->sp.x = ((*info)->map[hgt][wdt]->wp.x
					+ (*info)->map[hgt][wdt]->wp.y)
					* (*info)->tile_size.x + SCREEN_MG;
			(*info)->map[hgt][wdt]->sp.y = ((*info)->map[hgt][wdt]->wp.y
						- (*info)->map[hgt][wdt]->wp.x) * (*info)->tile_size.y
						+ (*info)->sc_size.y / 2 + hgt_offset / 2
						* (*info)->tile_size.y - (*info)->map[hgt][wdt]->wp.z
						* (*info)->tile_size.y * SCALE_Z;
			wdt++;
		}
		hgt++;
	}
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

void	set_sizes(t_info **info)
{
	int	x_size;
	int	y_size;

	x_size = (*info)->map_size.x;
	y_size = (*info)->map_size.y;
	(*info)->tile_size.x = (SCREEN_W - (SCREEN_MG * 2)) / (x_size + y_size);
	if ((*info)->tile_size.x < MIN_TILE_SIZE)
		(*info)->tile_size.x = MIN_TILE_SIZE;
	(*info)->tile_size.y = (*info)->tile_size.x / 2;
	(*info)->map_r_size.x = (x_size + y_size) * ((*info)->tile_size.x);
	(*info)->map_r_size.y = (x_size + y_size) * ((*info)->tile_size.y);
	if ((*info)->map_r_size.x == 0 || (*info)->map_r_size.y == 0)
		close_fdf(1, "Error: Wrong map sizes", info);
	(*info)->sc_size.x = (*info)->map_r_size.x + SCREEN_MG * 2;
	(*info)->sc_size.y = (*info)->map_r_size.y  + SCREEN_MG * 2;
}
