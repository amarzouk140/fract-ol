/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayman_marzouk <ayman_marzouk@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 08:26:35 by amarzouk          #+#    #+#             */
/*   Updated: 2024/03/22 01:36:17 by ayman_marzo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int get_psychedelic_color(int iteration, int max_iterations) {
    if (iteration == max_iterations) return 0x000000; // Black for points inside the set

    // Create a base color palette that changes as iterations increase
    double t = (double)iteration / (double)max_iterations;
    int r = (int)(8.5 * sin(t * 2 * M_PI) * sin(t * 2 * M_PI) * 255);
    int g = (int)(9.5 * sin(t * 4 * M_PI) * sin(t * 4 * M_PI) * 255);
    int b = (int)(8.5 * cos(t * 4 * M_PI) * cos(t * 4 * M_PI) * 255);

    // Combine the color components and return the color
    return (r << 16) | (g << 8) | b;
}

// void	mandel_vs_julia(t_complex *z, t_complex *c, t_fractal *fractal)
// {
// 	if (!ft_strcmp(fractal->name, "julia"))
// 	{
// 		c->x = fractal->julia_x;
// 		c->y = fractal->julia_y;
// 	}
// 	else
// 	{
// 		c->x = z->x;
// 		c->y = z->y;
// 	}
// }

static void my_pixel_put(int x, int y, t_img *img, int color) {
    int offset;

    offset = (y * img->line_len) + (x * (img->bpp / 8));
    *(unsigned int*)(img->pixels_ptr + offset) = color;
}

static t_complex abs_complex(t_complex z) {
    t_complex result;
    result.x = fabs(z.x);
    result.y = fabs(z.y);
    return result;
}

static void handle_pixel(int x, int y, t_fractal *fractal) {
    t_complex z;
    t_complex c = {0, 0};
    int i = 0;

    z.x = map(x, -2, +2, WIDTH) * fractal->zoom + fractal->shift_x;
    z.y = map(y, +2, -2, HEIGHT) * fractal->zoom + fractal->shift_y;
    
    if (!ft_strcmp(fractal->name, "burning_ship")) {
        c.x = z.x;
        c.y = z.y;
        z.x = 0;
        z.y = 0;
    } else if (!ft_strcmp(fractal->name, "julia")) {
        c.x = fractal->julia_x;
        c.y = fractal->julia_y;
    } else { // Mandelbrot setup
        c.x = z.x;
        c.y = z.y;
        z.x = 0;
        z.y = 0;
    }

    while (i < fractal->iterations) {
        if (!ft_strcmp(fractal->name, "burning_ship")) {
            z = abs_complex(z);
        }
        z = sum_complex(square_complex(z), c);

        if ((z.x * z.x) + (z.y * z.y) > fractal->escape_value) {
            int color = get_psychedelic_color(i, fractal->iterations);
            my_pixel_put(x, y, &fractal->img, color);
            return;
        }
        i++;
    }
    my_pixel_put(x, y, &fractal->img, BLACK); // Points inside the set
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
