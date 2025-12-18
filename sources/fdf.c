/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:51:22 by mperrine          #+#    #+#             */
/*   Updated: 2025/12/19 00:11:06 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

void	ft_mlx_init(t_info **info)
{
	(*info)->mlx = mlx_init();
	(*info)->info = (mlx_window_create_info){
		.render_target = NULL, .title = "FdF", .width = SCREEN_SIZE_X,
		.height = SCREEN_SIZE_Y, .is_fullscreen = false, .is_resizable = false};
	(*info)->win = mlx_new_window((*info)->mlx, &(*info)->info);
	(*info)->image = mlx_new_image((*info)->mlx, SCREEN_SIZE_X, SCREEN_SIZE_Y);
	mlx_on_event((*info)->mlx, (*info)->win, MLX_KEYDOWN, close_hk, &info);
	mlx_on_event((*info)->mlx, (*info)->win, MLX_WINDOW_EVENT, close_hk, &info);
}

int	main(int ac, char **av)
{
	t_info	*info;

	if (ac != 2)
		return (1);
	info = malloc(sizeof(t_info));
	if (!info)
		close_fdf(2, "Error: Malloc failed", NULL);
	parse_map(&info, av[1]);
	ft_mlx_init(&info);
	show_vertexs(&info);
	mlx_loop(info->mlx);
}
