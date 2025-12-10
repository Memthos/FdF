/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 11:51:36 by mperrine          #+#    #+#             */
/*   Updated: 2025/12/10 10:21:17 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/MacroLibX/includes/mlx.h"
# include "../libs/libft_tools/headers/libft.h"

# include <stdio.h>
# include <math.h>
# include <fcntl.h>

typedef struct s_vector
{
	int	x;
	int	y;
	int	z;
}		t_vector;

typedef struct s_mlx_win
{
	mlx_window				win;
	mlx_window_create_info	info;
	mlx_image				image;
}							t_mlx_win;

#endif