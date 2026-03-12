/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:23:49 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/12 21:20:20 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

long	ft_abs(long nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	if (!tab || !*tab)
		return ;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

static void	clear_map(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->map_size.y)
		free(info->map[i++]);
	free(info->map);
}

static void	close_win(t_info *info)
{
	if (info->mlx)
	{
		mlx_loop_end(info->mlx);
		mlx_destroy_image(info->mlx, info->img);
		mlx_destroy_window(info->mlx, info->win);
		mlx_destroy_context(info->mlx);
	}
	if (info->map)
		clear_map(info);
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
