/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 08:59:27 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/06 16:41:49 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	isometric_projection(t_info **info)
{
	int			l_nb;
	int			l_pos;
	t_vector_2	half;

	half = (t_vector_2){(*info)->tile_size.x / 2, (*info)->tile_size.y / 2};
	l_nb = -1;
	while ((*info)->map[++l_nb])
	{
		l_pos = -1;
		while ((*info)->map[l_nb][++l_pos])
		{
			(*info)->map[l_nb][l_pos]->sp.x = (((*info)->map[l_nb][l_pos]->wp.x
						- (*info)->map[l_nb][l_pos]->wp.y) * half.x)
				+ ((*info)->sc_size.x / 2) - half.x;
			(*info)->map[l_nb][l_pos]->sp.y = (((*info)->map[l_nb][l_pos]->wp.x
						+ (*info)->map[l_nb][l_pos]->wp.y) * half.y)
				- ((*info)->map[l_nb][l_pos]->wp.z * (half.y / 2))
				+ ((*info)->sc_size.y / 2);
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

void	set_sizes(t_info **info)
{
	int	l_nb;
	int	l_pos;
	int	max_wdt;

	l_nb = -1;
	max_wdt = 0;
	while ((*info)->map[++l_nb])
	{
		l_pos = 0;
		while ((*info)->map[l_nb][l_pos])
			l_pos++;
		if (l_pos > max_wdt)
			max_wdt = l_pos;
	}
	(*info)->tile_size = (t_vector_2){SCREEN_W / (max_wdt - 1), SCREEN_H / l_nb};
	if ((*info)->tile_size.x < (*info)->tile_size.y)
		(*info)->tile_size.y = (*info)->tile_size.x / 2;
	else
		(*info)->tile_size.x = (*info)->tile_size.y * 2;
	(*info)->sc_size.x = (max_wdt - 1) * (*info)->tile_size.x;
	(*info)->sc_size.y = l_nb * (*info)->tile_size.y;
}
