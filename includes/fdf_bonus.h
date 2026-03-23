/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:51:36 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/23 15:21:14 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "../libs/MacroLibX/includes/mlx.h"
# include "../libs/libft_tools/headers/libft.h"

# include <stdio.h>
# include <math.h>
# include <fcntl.h>

# define SCREEN_W 1600
# define SCREEN_H 900
# define SCREEN_MG 20
# define FOV 500.0

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
	t_vector_2	sp;
	mlx_color	col;
}				t_vinfo;

typedef struct s_info
{
	t_vector_2				map_size;
	t_vinfo					a;
	t_vinfo					b;
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
	t_vinfo					**map;
}							t_info;

void	reset_transforms(t_info *info);

int		check_file_format(t_info *info, char *file);
int		check_map(t_info *info, char *file);

void	parse_map(t_info *info, char *file);
void	draw_mesh(t_info *info);

void	set_coordinates(t_info *info);
void	isometric_projection(t_info *info);
void	perspective_projection(t_info *info);

void	key_hk(int key, void *param);
void	m_wheel_hk(int key, void *param);

int		ft_isspace(int c);
long	ft_abs(long nb);
double	ft_interp(double x1, double x2, double i);
void	free_tab(char **tab);
void	clear_map(t_info *info, int max);

void	close_fdf(int code, char *msg, t_info *info);

#endif
