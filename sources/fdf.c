/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:51:22 by mperrine          #+#    #+#             */
/*   Updated: 2025/12/10 10:57:18 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"
#include "../libs/MacroLibX/includes/mlx_extended.h"

static void	close_hook(int key, void *param)
{
	if (key == 41 || key == 0)
		mlx_loop_end(param);
}


int	main(void)
{
	mlx_context				mlx;
	t_mlx_win				main_win;

	mlx = mlx_init();
	main_win.info = (mlx_window_create_info){
		.render_target = NULL,
		.title = "FdF",
		.width = 1280,
		.height = 720,
		.is_fullscreen = false,
		.is_resizable = false};
	main_win.win = mlx_new_window(mlx, &main_win.info);
	mlx_on_event(mlx, main_win.win, MLX_KEYDOWN, close_hook, mlx);
	mlx_on_event(mlx, main_win.win, MLX_WINDOW_EVENT, close_hook, mlx);
	mlx_loop(mlx);
	mlx_destroy_window(mlx, main_win.win);
	mlx_destroy_context(mlx);
}
