/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 11:16:16 by mperrine          #+#    #+#             */
/*   Updated: 2025/12/12 13:01:18 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

static void	clear_map(t_info **info)
{
	int	i;

	i = -1;
	while ((*info)->map[i++])
		free((*info)->map[i]);
	free((*info)->map);
}

void	close_win(t_info **info)
{
	mlx_loop_end((*info)->mlx);
	mlx_destroy_window((*info)->mlx, (*info)->draw.win);
	mlx_destroy_image((*info)->mlx, (*info)->draw.image);
	mlx_destroy_window((*info)->mlx, (*info)->main.win);
	mlx_destroy_context((*info)->mlx);
	clear_map(info);
	free(*info);
}

void	close_fdf(int code, char *msg, t_info **info)
{
	if (code != 0)
	{
		if (msg)
			ft_putendl_fd(msg, 2);
		else
			perror("Error");
	}
	if (info || *info)
		close_win(info);
	exit(code);
}

void	close_hook(int key, void *param)
{
	if (key == 41 || key == 0)
		close_fdf(0, NULL, param);
}
