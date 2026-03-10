/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 08:59:27 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/09 17:16:11 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	isometric_projection(t_info **info)
{
	int			cur_hgt;
	int			cur_wdt;

	cur_hgt = 0;
	while ((*info)->map[cur_hgt++])
	{
		cur_wdt = 0;
		while ((*info)->map[cur_hgt - 1][cur_wdt++])
		{
			(*info)->map[cur_hgt - 1][cur_wdt - 1]->sp.x = ((*info)->map[cur_hgt - 1][cur_wdt - 1]->wp.x
					+ (*info)->map[cur_hgt - 1][cur_wdt - 1]->wp.y) * (*info)->tile_size.x + SCREEN_MG;
			(*info)->map[cur_hgt - 1][cur_wdt - 1]->sp.y = ((*info)->map[cur_hgt - 1][cur_wdt - 1]->wp.y
						- (*info)->map[cur_hgt - 1][cur_wdt - 1]->wp.x) * (*info)->tile_size.y
						+ (*info)->sc_size.y / 2
						- (*info)->map[cur_hgt - 1][cur_wdt - 1]->wp.z * (*info)->tile_size.y * SCALE_Z;
		}
	}
}

// void	isometric_projection(t_info **info)
// {
// 	int			l_nb;
// 	int			l_pos;
// 	t_vector_2	half;

// 	half = (t_vector_2){(*info)->tile_size.x / 2, (*info)->tile_size.y / 2};
// 	l_nb = -1;
// 	while ((*info)->map[++l_nb])
// 	{
// 		l_pos = -1;
// 		while ((*info)->map[l_nb][++l_pos])
// 		{
// 			(*info)->map[l_nb][l_pos]->sp.x = ((*info)->map[l_nb][l_pos]->wp.x
// 					+ (*info)->map[l_nb][l_pos]->wp.y) * half.x + SCREEN_MG;
// 			(*info)->map[l_nb][l_pos]->sp.y = ((*info)->map[l_nb][l_pos]->wp.y
// 					- (*info)->map[l_nb][l_pos]->wp.x) * half.y
// 				- (*info)->map[l_nb][l_pos]->wp.z * half.y
// 				+ ((*info)->map_size.x - 1) * half.y;
// 		}
// 	}
// }

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

static void	set_real_map_size(t_info **info)
{
	int	x;
	int	y;

	x = (*info)->map_size.x;
	y = (*info)->map_size.y;
	(*info)->map_r_size.x = sqrt(x * x + y * y);
	(*info)->map_r_size.y = (*info)->map_r_size.x / 2;
}

void	set_sizes(t_info **info)
{
	int	tiles_w;
	int	tiles_h;

	set_real_map_size(info);
	if ((*info)->map_r_size.x == 0 || (*info)->map_r_size.y == 0)
		close_fdf(1, "Error: Wrong map sizes", info);
	tiles_w = (SCREEN_W - (SCREEN_MG * 2)) / (*info)->map_r_size.x;
	tiles_h = (SCREEN_H - (SCREEN_MG * 2)) / (*info)->map_r_size.y;
	if (tiles_w / 2 < tiles_h)
		(*info)->tile_size.x = tiles_h;
	else
		(*info)->tile_size.x = tiles_w;
	if ((*info)->tile_size.x < MIN_TILE_SIZE)
		(*info)->tile_size.x = MIN_TILE_SIZE;
	(*info)->tile_size.y = (*info)->tile_size.x / 2;
	(*info)->sc_size.x = (*info)->map_r_size.x * (*info)->tile_size.x + SCREEN_MG * 2;
	(*info)->sc_size.y = (*info)->sc_size.x / 2;
}
