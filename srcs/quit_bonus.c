/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 14:46:42 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/23 14:21:37 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

static void	close_win(t_info *info)
{
	if (info->mlx)
		mlx_loop_end(info->mlx);
	if (info->img)
		mlx_destroy_image(info->mlx, info->img);
	if (info->win)
		mlx_destroy_window(info->mlx, info->win);
	if (info->mlx)
		mlx_destroy_context(info->mlx);
	if (info->map)
		clear_map(info, info->map_size.y);
}

void	close_fdf(int code, char *msg, t_info *info)
{
	if (code != 0)
	{
		if (msg)
			ft_putendl_fd(msg, 2);
		else
			perror("Error");
	}
	if (info)
		close_win(info);
	exit(code);
}
