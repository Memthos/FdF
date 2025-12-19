/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:26:33 by mperrine          #+#    #+#             */
/*   Updated: 2025/12/19 14:10:31 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	show_vertexs(t_info **info)
{
	int	l_nb;
	int	l_pos;

	l_nb = -1;
	while ((*info)->map[++l_nb])
	{
		l_pos = -1;
		while ((*info)->map[l_nb][++l_pos])
			mlx_set_image_pixel((*info)->mlx, (*info)->image,
				(*info)->map[l_nb][l_pos]->sp.x,
				(*info)->map[l_nb][l_pos]->sp.y,
				(*info)->map[l_nb][l_pos]->col);
	}
	mlx_put_image_to_window((*info)->mlx, (*info)->win, (*info)->image, 0, 0);
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
	(*info)->tile_size = (t_vector_2){32, 16};
	(*info)->sc_size.x = (max_wdt - 1) * (*info)->tile_size.x;
	(*info)->sc_size.y = (*info)->sc_size.x / (*info)->tile_size.x
		* (*info)->tile_size.y;
}
