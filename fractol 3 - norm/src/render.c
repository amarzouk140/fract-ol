/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzouk <amarzouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 08:26:35 by amarzouk          #+#    #+#             */
/*   Updated: 2024/03/25 10:34:51 by amarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	my_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

static t_complex	abs_complex(t_complex z)
{
	t_complex	result;

	result.x = fabs(z.x);
	result.y = fabs(z.y);
	return (result);
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	z = (t_complex){0, 0};
	c = (t_complex){0, 0};
	i = 0;
	z.x = map(x, -2, +2, WIDTH) * fractal->zoom + fractal->shift_x;
	z.y = map(y, +2, -2, HEIGHT) * fractal->zoom + fractal->shift_y;
	if (!ft_strcmp(fractal->name, "burning_ship"))
	{
		c.x = z.x;
		c.y = z.y;
		z.x = 0;
		z.y = 0;
	}
	else if (!ft_strcmp(fractal->name, "julia"))
	{
		c.x = fractal->julia_x;
		c.y = fractal->julia_y;
	}
	else
	{
		c.x = z.x;
		c.y = z.y;
		z.x = 0;
		z.y = 0;
	}
	while (i < fractal->iterations)
	{
		if (!ft_strcmp(fractal->name, "burning_ship"))
		{
			z = abs_complex(z);
		}
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape_value)
		{
			color = get_psychedelic_color(i, fractal->iterations);
			my_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		i++;
	}
	my_pixel_put(x, y, &fractal->img, BLACK);
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
