/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:26:33 by mperrine          #+#    #+#             */
/*   Updated: 2025/12/18 23:25:49 by mperrine         ###   ########.fr       */
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
	mlx_put_image_to_window((*info)->mlx, (*info)->win, (*info)->image, 10, 10);
}