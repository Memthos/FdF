/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 08:59:27 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/23 14:30:24 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	isometric_projection(t_info *info)
{
	info->a.sp.x = (info->a.wp.x - info->a.wp.y) * cos(0.523599);
	info->a.sp.y = (info->a.wp.x + info->a.wp.y) * sin(0.523599) - info->a.wp.z;
	info->b.sp.x = (info->b.wp.x - info->b.wp.y) * cos(0.523599);
	info->b.sp.y = (info->b.wp.x + info->b.wp.y) * sin(0.523599) - info->b.wp.z;
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
	isometric_projection(info);
	info->a.sp.x += SCREEN_MG + (SCREEN_W - SCREEN_MG) / 2;
	info->b.sp.x += SCREEN_MG + (SCREEN_W - SCREEN_MG) / 2;
	info->a.sp.y += SCREEN_H / 2;
	info->b.sp.y += SCREEN_H / 2;
}
