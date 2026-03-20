/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:33:22 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/21 00:13:52 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	isometric_projection(t_info *info)
{
	info->a.sp.x = (info->a.wp.x - info->a.wp.y) * cos(0.523599);
	info->a.sp.y = (info->a.wp.x + info->a.wp.y) * sin(0.523599) - info->a.wp.z;
	info->b.sp.x = (info->b.wp.x - info->b.wp.y) * cos(0.523599);
	info->b.sp.y = (info->b.wp.x + info->b.wp.y) * sin(0.523599) - info->b.wp.z;
}

void	perspective_projection(t_info *info)
{
	double	scale;

	scale = FOV / (FOV + info->a.wp.z);
	info->a.sp.x = info->a.wp.x * scale;
	info->a.sp.y = info->a.wp.y * scale;
	scale = FOV / (FOV + info->b.wp.z);
	info->b.sp.x = info->b.wp.x * scale;
	info->b.sp.y = info->b.wp.y * scale;
}
