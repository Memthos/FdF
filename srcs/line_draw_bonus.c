/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 09:43:16 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/23 14:27:58 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

static mlx_color	get_color(long x, long y, t_info *info)
{
	long		dx;
	long		dy;
	double		interp;
	mlx_color	color;

	dx = info->b.sp.x - info->a.sp.x;
	dy = info->b.sp.y - info->a.sp.y;
	if (ft_abs(dx) > ft_abs(dy))
		interp = ft_interp(info->a.sp.x, info->b.sp.x, x);
	else
		interp = ft_interp(info->a.sp.y, info->b.sp.y, y);
	color.r = info->a.col.r + (info->b.col.r - info->a.col.r) * interp;
	color.g = info->a.col.g + (info->b.col.g - info->a.col.g) * interp;
	color.b = info->a.col.b + (info->b.col.b - info->a.col.b) * interp;
	color.a = 0xFF;
	return (color);
}

static void	x_major(long dx, long dy, t_info *info)
{
	long	decision_p;
	long	i;
	long	x;
	long	y;

	x = info->a.sp.x;
	y = info->a.sp.y;
	decision_p = 2 * ft_abs(dy) - ft_abs(dx);
	i = 0;
	while (i < ft_abs(dx))
	{
		x += (dx >= 0) - (dx < 0);
		if (decision_p < 0)
			decision_p = decision_p + 2 * ft_abs(dy);
		else
		{
			y += (dy >= 0) - (dy < 0);
			decision_p = decision_p + 2 * ft_abs(dy) - 2 * ft_abs(dx);
		}
		mlx_set_image_pixel(info->mlx, info->img, x, y, get_color(x, y, info));
		i++;
	}
}

static void	y_major(long dx, long dy, t_info *info)
{
	long	decision_p;
	long	i;
	long	x;
	long	y;

	x = info->a.sp.x;
	y = info->a.sp.y;
	decision_p = 2 * ft_abs(dx) - ft_abs(dy);
	i = 0;
	while (i < ft_abs(dy))
	{
		y += (dy >= 0) - (dy < 0);
		if (decision_p < 0)
			decision_p = decision_p + 2 * ft_abs(dx);
		else
		{
			x += (dx >= 0) - (dx < 0);
			decision_p = decision_p + 2 * ft_abs(dx) - 2 * ft_abs(dy);
		}
		mlx_set_image_pixel(info->mlx, info->img, x, y, get_color(x, y, info));
		i++;
	}
}

static	void	draw_line(t_vinfo v1, t_vinfo v2, t_info *info)
{
	long	dx;
	long	dy;

	info->a = v1;
	info->b = v2;
	set_coordinates(info);
	dx = info->b.sp.x - info->a.sp.x;
	dy = info->b.sp.y - info->a.sp.y;
	mlx_set_image_pixel(info->mlx, info->img, info->a.sp.x,
		info->a.sp.y, info->a.col);
	if (ft_abs(dx) > ft_abs(dy))
		x_major(dx, dy, info);
	else
		y_major(dx, dy, info);
}

void	draw_mesh(t_info *info)
{
	long	x;
	long	y;

	y = 0;
	mlx_destroy_image(info->mlx, info->img);
	info->img = mlx_new_image(info->mlx, SCREEN_W, SCREEN_H);
	if (!info->img)
		close_fdf(1, "Error: Mlx fail", info);
	while (y < info->map_size.y)
	{
		x = 0;
		while (x < info->map_size.x)
		{
			if (x + 1 < info->map_size.x)
				draw_line((info->map[y][x]), (info->map[y][x + 1]), info);
			if (y + 1 < info->map_size.y)
				draw_line((info->map[y][x]), (info->map[y + 1][x]), info);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img, 0, 0);
}
