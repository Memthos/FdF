/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_draw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 09:43:16 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/09 16:08:27 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	draw_bresenham_hor(t_info **info, t_vinfo *v1, t_vinfo *v2)
{
	t_vector_2		p;
	t_vector_2		distance;
	int				decision_p;
	int				direction;
	int				i;

	distance = (t_vector_2){abs(v2->sp.x - v1->sp.x), v2->sp.y - v1->sp.y};
	direction = (int) copysign(1, distance.y - 1e-9);
	distance.y *= direction;
	p = (t_vector_2){v1->sp.x, v1->sp.y};
	decision_p = 2 * distance.y - distance.x;
	i = -1;
	while (++i < distance.x)
	{
		mlx_set_image_pixel((*info)->mlx, (*info)->img, p.x + i, p.y, v1->col);
		if (decision_p >= 0)
		{
			p.y += direction;
			decision_p -= 2 * distance.x;
		}
		decision_p += 2 * distance.y;
	}
}

static void	draw_bresenham_ver(t_info **info, t_vinfo *v1, t_vinfo *v2)
{
	t_vector_2		p;
	t_vector_2		distance;
	int				decision_p;
	int				direction;
	int				i;

	distance = (t_vector_2){v2->sp.x - v1->sp.x, abs(v2->sp.y - v1->sp.y)};
	direction = distance.x / abs(distance.x);
	distance.x *= direction;
	p = (t_vector_2){v1->sp.x, v1->sp.y};
	decision_p = 2 * distance.x - distance.y;
	i = -1;
	while (++i < distance.y)
	{
		mlx_set_image_pixel((*info)->mlx, (*info)->img, p.x, p.y + i, v1->col);
		if (decision_p >= 0)
		{
			p.x += direction;
			decision_p -= 2 * distance.y;
		}
		decision_p += 2 * distance.x;
	}
}

static void	draw_line(t_info **info, t_vinfo *v1, t_vinfo *v2)
{
	t_vinfo	*tmp;

	if (!v1 || !v2)
		return ;
	if (abs(v2->sp.x - v1->sp.x) > abs(v2->sp.y - v1->sp.y))
	{
		if (v1->sp.x > v2->sp.x)
		{
			tmp = v1;
			v1 = v2;
			v2 = tmp;
		}
		draw_bresenham_hor(info, v1, v2);
	}
	else
	{
		if (v1->sp.y > v2->sp.y)
		{
			tmp = v1;
			v1 = v2;
			v2 = tmp;
		}
		draw_bresenham_ver(info, v1, v2);
	}
}

static int	get_next_line_value(t_info **info, int l_nb, int l_pos)
{
	int	i;

	if (!(*info)->map[l_nb + 1] || !(*info)->map[l_nb + 1][0])
		return (1);
	i = 0;
	while (++i < l_pos)
	{
		if (!(*info)->map[l_nb + 1][i])
			return (1);
	}
	return (0);
}

void	draw_mesh(t_info **info)
{
	int	l_nb;
	int	l_pos;

	l_nb = -1;
	while ((*info)->map[++l_nb])
	{
		l_pos = -1;
		while ((*info)->map[l_nb][++l_pos])
		{
			if ((*info)->map[l_nb][l_pos + 1])
				draw_line(info, (*info)->map[l_nb][l_pos],
					(*info)->map[l_nb][l_pos + 1]);
			if (!get_next_line_value(info, l_nb, l_pos))
				draw_line(info, (*info)->map[l_nb][l_pos],
					(*info)->map[l_nb + 1][l_pos]);
		}
	}
	mlx_put_image_to_window((*info)->mlx, (*info)->win, (*info)->img, 0, 0);
}
