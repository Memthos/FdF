/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:16:16 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/12 15:55:23 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	key_hk(int key, void *param)
{
	if (key == 41 || key == 0)
		close_fdf(0, NULL, (t_info *)param);
	printf("KEY:%d\n", key);
}

void	m_wheel_hk(int key, void *param)
{
	(void)param;
	if (key == 1)
		printf("ZOOM\n");
	else if (key == 2)
		printf("DEZOOM\n");
}
