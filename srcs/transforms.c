/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 08:59:27 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/14 13:58:58 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	rotate_pitch(t_info *info)
{
	int	tmp;

	tmp = info->a.wp.x;
	info->a.wp.x = tmp * cos(info->pitch) + info->a.wp.z * sin(info->pitch);
	info->a.wp.z = info->a.wp.z * cos(info->pitch) - tmp * sin(info->pitch);
	tmp = info->b.wp.x;
	info->b.wp.x = tmp * cos(info->pitch) + info->b.wp.z * sin(info->pitch);
	info->b.wp.z = info->b.wp.z * cos(info->pitch) - tmp * sin(info->pitch);
}

static void	rotate_yaw(t_info *info)
{
	int	tmp;

	tmp = info->a.wp.x;
	info->a.wp.x = tmp * cos(info->yaw) - info->a.wp.y * sin(info->yaw);
	info->a.wp.y = tmp * sin(info->yaw) + info->a.wp.y * cos(info->yaw);
	tmp = info->b.wp.x;
	info->b.wp.x = tmp * cos(info->yaw) - info->b.wp.y * sin(info->yaw);
	info->b.wp.y = tmp * sin(info->yaw) + info->b.wp.y * cos(info->yaw);
}

static void	rotate_roll(t_info *info)
{
	int	tmp;

	tmp = info->a.wp.y;
	info->a.wp.y = tmp * cos(info->roll) - info->a.wp.z * sin(info->roll);
	info->a.wp.z = tmp * sin(info->roll) + info->a.wp.z * cos(info->roll);
	tmp = info->b.wp.y;
	info->b.wp.y = tmp * cos(info->roll) - info->b.wp.z * sin(info->roll);
	info->b.wp.z = tmp * sin(info->roll) + info->b.wp.z * cos(info->roll);
}

void	set_coordinates(t_info *info)
{
	info->a.wp.x -= info->map_size.x / 2;
	info->b.wp.x -= info->map_size.x / 2;
	info->a.wp.y -= info->map_size.y / 2;
	info->b.wp.y -= info->map_size.y / 2;
	info->a.wp.x *= info->zoom;
	info->b.wp.x *= info->zoom;
	info->b.wp.y *= info->zoom;
	info->a.wp.y *= info->zoom;
	info->a.wp.z *= info->zoom;
	info->b.wp.z *= info->zoom;
	rotate_pitch(info);
	rotate_yaw(info);
	rotate_roll(info);
	if (info->proj_type == 3)
		isometric_projection(info);
	else
		cavalier_projection(info);
	info->a.sp.x += SCREEN_MG + (SCREEN_W - SCREEN_MG) / 2 + info->translate_x;
	info->b.sp.x += SCREEN_MG + (SCREEN_W - SCREEN_MG) / 2 + info->translate_x;
	info->a.sp.y += SCREEN_H / 2 + info->translate_y;
	info->b.sp.y += SCREEN_H / 2 + info->translate_y;
}
