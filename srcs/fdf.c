/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:51:22 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/12 16:04:04 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	init_mlx(t_info **info)
{
	mlx_window_create_info	win_info;

	(*info)->screen_size.x = (*info)->map_size.x + (*info)->map_size.y
		+ SCREEN_MG * 2;
	(*info)->screen_size.y = (*info)->map_size.x + (*info)->map_size.y
		+ SCREEN_MG * 2;
	(*info)->mlx = mlx_init();
	win_info = (mlx_window_create_info){.title = "FdF",
		.width = (*info)->screen_size.x, .height = (*info)->screen_size.y,};
	(*info)->win = mlx_new_window((*info)->mlx, &win_info);
	(*info)->img = mlx_new_image((*info)->mlx,
			(*info)->screen_size.x, (*info)->screen_size.y);
	mlx_set_fps_goal((*info)->mlx,60);
	mlx_on_event((*info)->mlx, (*info)->win, MLX_KEYDOWN, key_hk, *info);
	mlx_on_event((*info)->mlx, (*info)->win, MLX_WINDOW_EVENT, key_hk, *info);
	mlx_on_event((*info)->mlx, (*info)->win, MLX_MOUSEWHEEL, m_wheel_hk, *info);
	mlx_add_loop_hook((*info)->mlx, draw_mesh, *info);
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
	info->proj_type = 1;
	parse_map(&info, av[1]);
	init_mlx(&info);
	mlx_loop(info->mlx);
}
