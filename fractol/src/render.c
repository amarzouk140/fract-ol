/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayman_marzouk <ayman_marzouk@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 08:26:35 by amarzouk          #+#    #+#             */
/*   Updated: 2024/02/09 14:08:43 by ayman_marzo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	blend_colours(int colour1, int colour2, double t) //Define a colour blending function that interpolates between two colours
{
	int	r; //To store the red component of the blended colour
	int	g; //To store the green component of the blended colour
	int	b; //To store the blue component of the blended colour

	//For each rgb calculation, it's a linear interpolation between colour1 and colour2
	//`5` is arbitrary value to determin dominance of colour2
	r = (int)((1 - t) * ((colour1 >> 16) & 0xFF) + t * ((colour2 >> 16) & 0xFF) * 5); //Calculate the red component of the blended colour. The >> 16 operation extracts the red component (the most significant 8 bits) from each colour. The & 0xFF operation ensures we only consider the lower 8 bits. The formula calculates the blended red component using t
	g = (int)((1 - t) * ((colour1 >> 8) & 0xFF) + t * ((colour2 >> 8) & 0xFF) * 5); //Similarly, calculate the green component of the blended colour. See #1
	b = (int)((1 - t) * (colour1 & 0xFF) + t * (colour2 & 0xFF) * 5); //Similarly, calculate the blue component of the blended colour

	// Increase the intensity or brightness with a larger adjustment factor
	r = (int)(r + (255 - r) * t * 1.5); //Increase the intensity or brightness of the red component based on the value of t. It adjusts the red component to make it brighter
	g = (int)(g + (255 - g) * t * 0.2); //Similarly, adjust the green component to control its brightness
	b = (int)(b + (255 - b) * t * 4); //Similarly, adjust the blue component to control its brightness
	return ((r << 16) | (g << 8) | b); //Return the combined adjusted colour channels
}

static void	mandel_vs_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strcmp(fractal->name, "julia"))
	{
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}

static void	my_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.x = (map(x, -2, +2, WIDTH) * fractal->zoom) + fractal->shift_x;
	z.y = (map(y, +2, -2, HEIGHT) * fractal->zoom) + fractal->shift_y;
	mandel_vs_julia(&z, &c, fractal);
	while (i < fractal->iterations)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape_value)
		{
			color =  blend_colours(BLACK, fractal->current_colour, (double)i / fractal->iterations);
			// color = map(i, BLACK, WHITE, fractal->iterations);
			my_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		++i;
	}
	my_pixel_put(x, y, &fractal->img, WHITE);
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
