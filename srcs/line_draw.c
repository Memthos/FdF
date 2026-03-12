/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 09:43:16 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/12 16:03:32 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	draw_bresenham_hor(t_info *info, t_vinfo *a, t_vinfo *b)
{
	t_vector_2		p;
	t_vector_2		distance;
	int				decision_p;
	int				direction;
	int				i;

	distance = (t_vector_2){ft_abs(b->iso.x - a->iso.x), b->iso.y - a->iso.y};
	direction = (int) copysign(1, distance.y - 1e-9);
	distance.y *= direction;
	p = (t_vector_2){a->iso.x, a->iso.y};
	decision_p = 2 * distance.y - distance.x;
	i = -1;
	while (++i < distance.x)
	{
		mlx_set_image_pixel(info->mlx, info->img, p.x + i, p.y, a->col);
		if (decision_p >= 0)
		{
			p.y += direction;
			decision_p -= 2 * distance.x;
		}
		decision_p += 2 * distance.y;
	}
}

static void	draw_bresenham_ver(t_info *info, t_vinfo *a, t_vinfo *b)
{
	t_vector_2		p;
	t_vector_2		distance;
	int				decision_p;
	int				direction;
	int				i;

	distance = (t_vector_2){b->iso.x - a->iso.x, ft_abs(b->iso.y - a->iso.y)};
	direction = distance.x / ft_abs(distance.x);
	distance.x *= direction;
	p = (t_vector_2){a->iso.x, a->iso.y};
	decision_p = 2 * distance.x - distance.y;
	i = -1;
	while (++i < distance.y)
	{
		mlx_set_image_pixel(info->mlx, info->img, p.x, p.y + i, a->col);
		if (decision_p >= 0)
		{
			p.x += direction;
			decision_p -= 2 * distance.y;
		}
		decision_p += 2 * distance.x;
	}
}

static void	draw_line(t_vinfo *a, t_vinfo *b, t_info *info)
{
	t_vinfo	*tmp;

	if (!a || !b)
		return ;
	if (ft_abs(b->iso.x - a->iso.x) > ft_abs(b->iso.y - a->iso.y))
	{
		if (a->iso.x > b->iso.x)
		{
			tmp = a;
			a = b;
			b = tmp;
		}
		draw_bresenham_hor(info, a, b);
	}
	else
	{
		if (a->iso.y > b->iso.y)
		{
			tmp = a;
			a = b;
			b = tmp;
		}
		draw_bresenham_ver(info, a, b);
	}
}

static	void	draw_l_init(t_vinfo a, t_vinfo b, t_info *info)
{
	set_coordinates(&a, &b, info);
	draw_line(&a, &b, info);
}

void	draw_mesh(void *data)
{
	t_info	*info;
	int	x;
	int	y;

	info = (t_info *)data;
	x = 0;
	while (++x < info->map_size.y)
	{
		y = 0;
		while (y < info->map_size.x)
		{
			if (x + 1 < info->map_size.x)
				draw_l_init(*(info->map[x][y]), *(info->map[x + 1][y]), info);
			if (y + 1 < info->map_size.y)
				draw_l_init(*(info->map[x][y]), *(info->map[x][y + 1]), info);
			y++;
		}
		x++;
	}
	mlx_clear_window(info->mlx, info->win, (mlx_color){.rgba = 0x000000FF});
	mlx_put_image_to_window(info->mlx, info->win, info->img, 0, 0);
}
