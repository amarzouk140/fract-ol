/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzouk <amarzouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 08:24:56 by amarzouk          #+#    #+#             */
/*   Updated: 2024/03/25 10:28:51 by amarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	map(double unscaled_num, double new_min, double new_max, double old_max)
{
	double	old_min;

	old_min = 0;
	return ((new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min)
		+ new_min);
}

t_complex	sum_complex(t_complex z1, t_complex z2)
{
	t_complex	result;

	result.x = z1.x + z2.x;
	result.y = z1.y + z2.y;
	return (result);
}

t_complex	square_complex(t_complex z)
{
	t_complex	result;

	result.x = (z.x * z.x) - (z.y * z.y);
	result.y = 2 * z.x * z.y;
	return (result);
}

int	get_psychedelic_color(int iteration, int max_iterations)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iteration == max_iterations)
		return (0x000000);
	t = (double)iteration / (double)max_iterations;
	r = (int)(8.5 * sin(t * 2 * M_PI) * sin(t * 2 * M_PI) * 255);
	g = (int)(9.5 * sin(t * 4 * M_PI) * sin(t * 4 * M_PI) * 255);
	b = (int)(8.5 * cos(t * 4 * M_PI) * cos(t * 4 * M_PI) * 255);
	return ((r << 16) | (g << 8) | b);
}
