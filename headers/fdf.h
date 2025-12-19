/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:51:36 by mperrine          #+#    #+#             */
/*   Updated: 2025/12/19 14:10:55 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/MacroLibX/includes/mlx.h"
# include "../libs/libft_tools/headers/libft.h"

# include <stdio.h>
# include <math.h>
# include <fcntl.h>

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
	t_vector_3	wp;
	t_vector_2	sp;
	mlx_color	col;
}				t_vertex_info;

typedef struct s_info
{
	t_vector_2				sc_size;
	t_vector_2				tile_size;
	mlx_context				mlx;
	mlx_window				win;
	mlx_window_create_info	info;
	mlx_image				image;
	t_vertex_info			***map;
}							t_info;

void		parse_map(t_info **info, char *file);
int			check_file_format(t_info **info, char *file);
u_int32_t	hex_to_rgba(const char *hex);
void		isometric_projection(t_info **info);
void		set_sizes(t_info **info);
void		ft_mlx_init(t_info **info);
void		show_vertexs(t_info **info);
void		close_hk(int key, void *param);
void		close_fdf(int code, char *msg, t_info **info);
void		close_win(t_info **info);
void		free_tab(char **tab);

#endif
