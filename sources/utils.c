/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mperrine <mperrine@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 22:23:49 by mperrine          #+#    #+#             */
/*   Updated: 2026/01/09 11:22:05 by mperrine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/fdf.h"

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
