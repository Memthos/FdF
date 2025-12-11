/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:51:36 by mperrine          #+#    #+#             */
/*   Updated: 2025/12/11 13:46:17 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/MacroLibX/includes/mlx.h"
# include "../libs/libft_tools/headers/libft.h"

# include <stdio.h>
# include <math.h>
# include <fcntl.h>

# define SCREEN_SIZE_X	1280
# define SCREEN_SIZE_Y	720
# define TILE_SIZE_X	32
# define TILE_SIZE_Y	16

typedef struct s_mlx_win
{
	mlx_window				win;
	mlx_window_create_info	info;
	mlx_image				image;
}							t_mlx_win;

typedef struct s_vector_3
{
	int	x;
	int	y;
	int	z;
}		t_vector_3;

typedef struct s_vector_2
{
	int	x;
	int	y;
}		t_vector_2;

typedef struct s_vertex_info
{
	t_vector_2	pos;
	mlx_color	col;
}				t_vertex_info;

void	world_to_screen(t_vertex_info *vertex, t_vector_3 *world);

#endif