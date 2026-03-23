/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:16:16 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/23 14:09:07 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

static int	movement_hk(int key, t_info *info)
{
	if (key == 26)
		info->translate_y -= 4;
	else if (key == 4)
		info->translate_x -= 4;
	else if (key == 22)
		info->translate_y += 4;
	else if (key == 7)
		info->translate_x += 4;
	else if (key == 13)
		info->yaw += 0.05;
	else if (key == 15)
		info->yaw -= 0.05;
	else if (key == 12)
		info->pitch -= 0.05;
	else if (key == 14)
		info->pitch += 0.05;
	else if (key == 18)
		info->roll += 0.05;
	else if (key == 24)
		info->roll -= 0.05;
	else
		return (0);
	return (1);
}

static int	projection_hk(int key, t_info *info)
{
	if (key == 30)
		info->proj_type = 1;
	else if (key == 31)
		info->proj_type = 2;
	else
		return (0);
	reset_transforms(info);
	return (1);
}

void	key_hk(int key, void *param)
{
	t_info	*info;

	info = (t_info *)param;
	if (key == 41 || key == 0)
		close_fdf(0, NULL, info);
	else if (movement_hk(key, info))
		draw_mesh(info);
	else if (projection_hk(key, info))
		draw_mesh(info);
	return ;
}

void	m_wheel_hk(int key, void *param)
{
	t_info	*info;

	info = (t_info *)param;
	if (key == 1)
		info->zoom += 1;
	else if (key == 2)
		info->zoom -= 1;
	else
		return ;
	draw_mesh(info);
}
