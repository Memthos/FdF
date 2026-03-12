/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 09:43:16 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/12 22:36:23 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	x_major(int dx, int dy, t_info *info)
{
	int				decision_p;
	int				i;

	decision_p = 2 * ft_abs(dy) - ft_abs(dx);
	i = 0;
	while (i < ft_abs(dx))
	{
		if (dx < 0)
			info->a.sp.x -= 1;
		else
			info->a.sp.x += 1;
		if (decision_p < 0)
			decision_p = decision_p + 2 * ft_abs(dy);
		else
		{
			if (dy < 0)
				info->a.sp.y -= 1;
			else
				info->a.sp.y += 1;
			decision_p = decision_p + 2 * ft_abs(dy) - 2 * ft_abs(dx);
		}
		mlx_set_image_pixel(info->mlx, info->img, info->a.sp.x,
			info->a.sp.y, info->a.col);
		i++;
	}
}

static void	y_major(int dx, int dy, t_info *info)
{
	int				decision_p;
	int				i;

	decision_p = 2 * ft_abs(dx) - ft_abs(dy);
	i = 0;
	while (i < ft_abs(dy))
	{
		if (dy < 0)
			info->a.sp.y -= 1;
		else
			info->a.sp.y += 1;
		if (decision_p < 0)
			decision_p = decision_p + 2 * ft_abs(dx);
		else
		{
			if (dx < 0)
				info->a.sp.x -= 1;
			else
				info->a.sp.x += 1;
			decision_p = decision_p + 2 * ft_abs(dx) - 2 * ft_abs(dy);
		}
		mlx_set_image_pixel(info->mlx, info->img, info->a.sp.x,
			info->a.sp.y, info->a.col);
		i++;
	}
}

static	void	draw_line(t_vinfo v1, t_vinfo v2, t_info *info)
{
	int	dx;
	int	dy;

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
	int	x;
	int	y;

	mlx_clear_window(info->mlx, info->win, (mlx_color){.rgba = 0x000000FF});
	y = 0;
	while (y < info->map_size.y)
	{
		x = 0;
		while (x < info->map_size.x)
		{
			if (x + 1 < info->map_size.x)
				draw_line((info->map[x][y]), (info->map[x + 1][y]), info);
			if (y + 1 < info->map_size.y)
				draw_line((info->map[x][y]), (info->map[x][y + 1]), info);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img, 0, 0);
}
