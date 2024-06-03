/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzouk <amarzouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 08:26:35 by amarzouk          #+#    #+#             */
/*   Updated: 2024/03/25 10:45:15 by amarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

void	my_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			handle_pixel(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->connect, fractal->window,
		fractal->img.img_ptr, 0, 0);
}
