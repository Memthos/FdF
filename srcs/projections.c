/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 15:33:22 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/12 15:34:03 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	isometric_projection(t_vinfo *a, t_vinfo *b)
{
	a->iso.x = (a->wp.x - a->wp.y) * cos(0.523599);
	a->iso.y = (a->wp.x + a->wp.y) * sin(0.523599) - a->wp.z;
	b->iso.x = (b->wp.x - b->wp.y) * cos(0.523599);
	b->iso.y = (b->wp.x + b->wp.y) * sin(0.523599) - b->wp.z;
}
