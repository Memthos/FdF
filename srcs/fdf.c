/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:51:22 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/11 15:06:27 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	init_mlx(t_info **info)
{
	(*info)->mlx = mlx_init();
	(*info)->info = (mlx_window_create_info){
		.render_target = NULL, .title = "FdF",
		.width = (*info)->sc_size.x, .height = (*info)->sc_size.y,
		.is_fullscreen = false, .is_resizable = false};
	(*info)->win = mlx_new_window((*info)->mlx, &(*info)->info);
	(*info)->img = mlx_new_image((*info)->mlx,
			(*info)->sc_size.x, (*info)->sc_size.y);
	mlx_set_fps_goal((*info)->mlx, 30);
	mlx_on_event((*info)->mlx, (*info)->win, MLX_KEYDOWN, close_hk, info);
	mlx_on_event((*info)->mlx, (*info)->win, MLX_WINDOW_EVENT, close_hk, info);
}

int	main(int ac, char **av)
{
	t_info	*info;

	if (ac != 2)
		close_fdf(2, "Error: Wrong number of arguments", NULL);
	info = malloc(sizeof(t_info));
	if (!info)
		close_fdf(2, "Error: Malloc failed", NULL);
	info->mlx = NULL;
	info->map = NULL;
	parse_map(&info, av[1]);
	set_sizes(&info);
	isometric_projection(&info);
	init_mlx(&info);
	draw_mesh(&info);
	mlx_loop(info->mlx);
}
