/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:51:36 by mperrine          #+#    #+#             */
/*   Updated: 2025/12/18 10:10:01 by mperrine         ###   ########.fr       */
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
	t_vector_3	wp;
	t_vector_2	sp;
	mlx_color	col;
}				t_vertex_info;

typedef struct s_info
{
	mlx_context		mlx;
	t_mlx_win		main;
	t_mlx_win		draw;
	t_vertex_info	***map;
}					t_info;

t_info		*ft_mlx_init(void);
void		parse_map(t_info **info, char *file);
int			check_file_format(t_info **info, char *file);
u_int32_t	hex_to_rgba(const char *hex);
void		close_fdf(int code, char *msg, t_info **info);
void		close_hk(int key, void *param);
void		close_win(t_info **info);
t_vector_2	world_to_screen(t_vertex_info *v);

#endif