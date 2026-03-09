/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:51:36 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/09 17:14:13 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/MacroLibX/includes/mlx.h"
# include "../libs/libft_tools/headers/libft.h"

# include <stdio.h>
# include <math.h>
# include <fcntl.h>

# define SCREEN_W 1600
# define SCREEN_H 900
# define SCREEN_MG 20
# define MIN_TILE_SIZE 4
# define SCALE_Z 2

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

typedef struct s_vinfo
{
	t_vector_3	wp;
	t_vector_2	sp;
	mlx_color	col;
}				t_vinfo;

typedef struct s_info
{
	t_vector_2				sc_size;
	t_vector_2				tile_size;
	t_vector_2				map_size;
	t_vector_2				map_r_size;
	mlx_context				mlx;
	mlx_window				win;
	mlx_window_create_info	info;
	mlx_image				img;
	t_vinfo					***map;
}							t_info;

void		parse_map(t_info **info, char *file);
int			check_file_format(t_info **info, char *file);
void		isometric_projection(t_info **info);
void		set_sizes(t_info **info);
void		show_vertexs(t_info **info);
void		draw_mesh(t_info **info);
void		close_hk(int key, void *param);
void		close_fdf(int code, char *msg, t_info **info);
void		close_win(t_info **info);
void		free_tab(char **tab);

#endif
