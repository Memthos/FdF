/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:16:16 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/12 22:39:42 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	key_hk(int key, void *param)
{
	t_info *info;

	info = (t_info *)param;
	if (key == 41 || key == 0)
	{
		close_fdf(0, NULL, info);
		return ;
	}
	else if (key == 26)
		info->translate_y -= 4;
	else if (key == 4)
		info->translate_x -= 4;
	else if (key == 22)
		info->translate_y += 4;
	else if (key == 7)
		info->translate_x += 4;
	else
		return ;
	draw_mesh(info);
}

void	m_wheel_hk(int key, void *param)
{
	t_info *info;

	info = (t_info *)param;
	if (key == 1)
		info->zoom += 1;
	else if (key == 2)
		info->zoom -= 1;
	else
		return ;
	draw_mesh(info);
}
