/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:51:22 by mperrine          #+#    #+#             */
/*   Updated: 2025/12/17 13:32:16 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

t_info	*ft_mlx_init(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		close_fdf(2, "Error: Malloc failed", NULL);
	info->map = NULL;
	info->mlx = mlx_init();
	info->main.info = (mlx_window_create_info){
		.render_target = NULL, .title = "FdF", .width = SCREEN_SIZE_X,
		.height = SCREEN_SIZE_Y, .is_fullscreen = false, .is_resizable = false};
	info->main.win = mlx_new_window(info->mlx, &info->main.info);
	info->draw.image = mlx_new_image(info->mlx, SCREEN_SIZE_X, SCREEN_SIZE_Y);
	info->draw.info = (mlx_window_create_info){
		.render_target = info->draw.image, .title = NULL, .width = 0,
		.height = 0, .is_fullscreen = false, .is_resizable = false};
	info->draw.win = mlx_new_window(info->mlx, &info->draw.info);
	mlx_on_event(info->mlx, info->main.win, MLX_KEYDOWN, close_hook, &info);
	mlx_on_event(info->mlx, info->main.win, MLX_WINDOW_EVENT, close_hook, &info);
	mlx_loop(info->mlx);
	return (info);
}

int	main(int ac, char **av)
{
	t_info	*info;

	if (ac != 2)
		return (1);
	info = ft_mlx_init();
	parse_map(&info, av[1]);
}

t_vector_2	world_to_screen(t_vertex_info *v)
{
	t_vector_2	screen;
	screen.x = (v->wp.x - v->wp.y) * TILE_SIZE_X / 2;
	screen.y = (v->wp.x + v->wp.y) * TILE_SIZE_Y / 2 - v->wp.z;
	return (screen);
}
