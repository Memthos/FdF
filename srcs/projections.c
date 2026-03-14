/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:33:22 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/14 14:07:27 by mperrine         ###   ########.fr       */
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

void	oblique_projection(t_info *info)
{
	info->a.sp.x = info->a.wp.x - info->a.wp.z * cos(0.785398);
	info->a.sp.y = info->a.wp.y - info->a.wp.z * sin(0.785398);
	info->b.sp.x = info->b.wp.x - info->b.wp.z * cos(0.785398);
	info->b.sp.y = info->b.wp.y - info->b.wp.z * sin(0.785398);
}
