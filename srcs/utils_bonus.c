/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:23:49 by mperrine          #+#    #+#             */
/*   Updated: 2026/03/23 15:21:54 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

long	ft_abs(long nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

double	ft_interp(double x1, double x2, double i)
{
	if (x1 != x2)
		return ((i - x1) / (x2 - x1));
	return (0);
}

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	if (!tab || !*tab)
		return ;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	clear_map(t_info *info, int max)
{
	int	i;

	i = 0;
	while (i < max)
		free(info->map[i++]);
	free(info->map);
	info->map = NULL;
}
