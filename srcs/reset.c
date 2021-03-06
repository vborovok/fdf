/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yquaro <yquaro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:38:37 by yquaro            #+#    #+#             */
/*   Updated: 2020/11/04 14:38:38 by yquaro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	reset_all(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < mlx->img->grid_square)
	{
		mlx->img->point[i] = mlx->img->reset_point[i];
		i++;
	}
	mlx->img->camera->alpha = 0;
	mlx->img->camera->beta = 0;
	mlx->img->camera->gamma = 0;
	mlx->img->margin_x = MARGIN_X;
	mlx->img->margin_y = MARGIN_Y;
}
