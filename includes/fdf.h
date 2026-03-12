/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:51:36 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/12 15:55:41 by mperrine         ###   ########.fr       */
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
# define SCALE_Z 1

typedef struct s_vector_3
{
	long	x;
	long	y;
	long	z;
}		t_vector_3;

typedef struct s_vector_2
{
	long	x;
	long	y;
}		t_vector_2;

typedef struct s_vinfo
{
	t_vector_3	wp;
	t_vector_2	iso;
	mlx_color	col;
}				t_vinfo;

typedef struct s_info
{
	t_vector_2				screen_size;
	t_vector_2				map_size;
	int						proj_type;
	long					translate_x;
	long					translate_y;
	long					zoom;
	double					pitch;
	double					yaw;
	double					roll;
	mlx_context				mlx;
	mlx_window				win;
	mlx_image				img;
	t_vinfo					***map;
}							t_info;

void	parse_map(t_info **info, char *file);
int		check_file_format(t_info **info, char *file);
int		check_map(t_info **info, char *file);
long	ft_abs(long nb);
void	isometric_projection(t_vinfo *a, t_vinfo *b);
void	set_coordinates(t_vinfo *a, t_vinfo *b, t_info *info);
void	draw_mesh(void *data);
void	key_hk(int key, void *param);
void	m_wheel_hk(int key, void *param);
void	close_fdf(int code, char *msg, t_info *info);
void	free_tab(char **tab);

#endif
