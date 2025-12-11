/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:51:22 by mperrine          #+#    #+#             */
/*   Updated: 2025/12/11 13:25:46 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

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
		.width = SCREEN_SIZE_X,
		.height = SCREEN_SIZE_Y,
		.is_fullscreen = false,
		.is_resizable = false};
	main_win.win = mlx_new_window(mlx, &main_win.info);
	mlx_on_event(mlx, main_win.win, MLX_KEYDOWN, close_hook, mlx);
	mlx_on_event(mlx, main_win.win, MLX_WINDOW_EVENT, close_hook, mlx);
	mlx_loop(mlx);
	mlx_destroy_window(mlx, main_win.win);
	mlx_destroy_context(mlx);
}

void	world_to_screen(t_vertex_info *vertex, t_vector_3 *world)
{
	vertex->pos.x = (world->x - world->y) * TILE_SIZE_X / 2;
	vertex->pos.y = (world->x + world->y) * TILE_SIZE_Y / 2 - world->z;
}