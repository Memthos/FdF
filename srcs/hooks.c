/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:16:16 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/23 14:10:43 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	key_hk(int key, void *param)
{
	t_info	*info;

	info = (t_info *)param;
	if (key == 41 || key == 0)
		close_fdf(0, NULL, info);
	return ;
}
