/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:51:22 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/23 14:46:52 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	reset_transforms(t_info *info)
{
	if (SCREEN_W / info->map_size.x > SCREEN_H / info->map_size.y)
		info->zoom = SCREEN_H / info->map_size.y;
	else
		info->zoom = SCREEN_W / info->map_size.x;
	info->translate_x = 0;
	info->translate_y = 0;
	info->pitch = 0;
	info->yaw = 0;
	info->roll = 0;
}

static int	init_mlx(t_info *info)
{
	mlx_window_create_info	win_info;

	info->mlx = mlx_init();
	if (!info->mlx)
		return (1);
	win_info = (mlx_window_create_info){NULL, "FdF", SCREEN_W, SCREEN_H, 0, 0};
	info->win = mlx_new_window(info->mlx, &win_info);
	if (!info->win)
		return (1);
	info->img = mlx_new_image(info->mlx, SCREEN_W, SCREEN_H);
	if (!info->img)
		return (1);
	mlx_set_fps_goal(info->mlx, 60);
	mlx_on_event(info->mlx, info->win, MLX_KEYDOWN, key_hk, info);
	mlx_on_event(info->mlx, info->win, MLX_WINDOW_EVENT, key_hk, info);
	mlx_on_event(info->mlx, info->win, MLX_MOUSEWHEEL, m_wheel_hk, info);
	return (0);
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac != 2)
		close_fdf(2, "Error: Wrong number of arguments", NULL);
	info.mlx = NULL;
	info.win = NULL;
	info.img = NULL;
	info.map = NULL;
	parse_map(&info, av[1]);
	if (init_mlx(&info))
		close_fdf(1, "Error: Mlx fail", &info);
	reset_transforms(&info);
	info.proj_type = 1;
	draw_mesh(&info);
	mlx_loop(info.mlx);
}
