/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 08:59:27 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/12 15:47:50 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	rotate_pitch(t_vinfo *a, t_vinfo *b, t_info *info)
{
	int	tmp;

	tmp = a->wp.x;
	a->wp.x = tmp * cos(info->pitch) + a->wp.z * sin(info->pitch);
	a->wp.z = a->wp.z * cos(info->pitch) - tmp * sin(info->pitch);
	tmp = b->wp.x;
	b->wp.x = tmp * cos(info->pitch) + b->wp.z * sin(info->pitch);
	b->wp.z = b->wp.z * cos(info->pitch) - tmp * sin(info->pitch);
}

static void	rotate_yaw(t_vinfo *a, t_vinfo *b, t_info *info)
{
	int	tmp;

	tmp = a->wp.x;
	a->wp.x = tmp * cos(info->yaw) - a->wp.y * sin(info->yaw);
	a->wp.y = tmp * sin(info->yaw) + a->wp.y * cos(info->yaw);
	tmp = b->wp.x;
	b->wp.x = tmp * cos(info->yaw) - b->wp.y * sin(info->yaw);
	b->wp.y = tmp * sin(info->yaw) + b->wp.y * cos(info->yaw);
}

static void	rotate_roll(t_vinfo *a, t_vinfo *b, t_info *info)
{
	int	tmp;

	tmp = a->wp.y;
	a->wp.y = tmp * cos(info->roll) - a->wp.z * sin(info->roll);
	a->wp.z = tmp * sin(info->roll) + a->wp.z * cos(info->roll);
	tmp = b->wp.y;
	b->wp.y = tmp * cos(info->roll) - b->wp.z * sin(info->roll);
	b->wp.z = tmp * sin(info->roll) + b->wp.z * cos(info->roll);
}

void	set_coordinates(t_vinfo *a, t_vinfo *b, t_info *info)
{
	a->wp.x += info->screen_size.x;
	b->wp.x += info->screen_size.x;
	a->wp.y += info->screen_size.y;
	b->wp.y += info->screen_size.y;
	a->wp.x *= info->zoom;
	a->wp.y *= info->zoom;
	a->wp.z *= info->zoom;
	b->wp.x *= info->zoom;
	b->wp.y *= info->zoom;
	b->wp.z *= info->zoom;
	rotate_pitch(a, b, info);
	rotate_yaw(a, b, info);
	rotate_roll(a, b, info);
	if (info->proj_type == 1)
		isometric_projection(a, b);
	else
		return ;
}
