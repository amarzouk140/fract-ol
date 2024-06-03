/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzouk <amarzouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 22:42:45 by ayman_marzo       #+#    #+#             */
/*   Updated: 2024/03/25 09:13:46 by amarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	malloc_error(void)
{
	perror("Problems with malloc");
	exit(1);
}

static void	events_init(t_fractal *fractal)
{
	mlx_hook(fractal->window, 2, 1L << 0, key_handler, fractal);
	mlx_hook(fractal->window, 4, 1L << 2, mouse_handler, fractal);
	mlx_hook(fractal->window, 17, 0, close_handler, fractal);
	mlx_hook(fractal->window, 6, 1L << 13, julia_track, fractal);
}

void	data_init(t_fractal *fractal)
{
	fractal->escape_value = 4;
	fractal->iterations = 42;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
	fractal->flag = 0;
}

void	fractal_init(t_fractal *fractal)
{
	fractal->connect = mlx_init();
	if (fractal->connect == NULL)
		malloc_error();
	fractal->window = mlx_new_window(fractal->connect, WIDTH, HEIGHT,
			fractal->name);
	if (fractal->window == NULL)
	{
		free(fractal->connect);
		malloc_error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->connect,
			WIDTH, HEIGHT);
	if (fractal->img.img_ptr == NULL)
	{
		mlx_destroy_window(fractal->connect, fractal->window);
		free(fractal->connect);
		malloc_error();
	}
	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bpp, &fractal->img.line_len, &fractal->img.endian);
	events_init(fractal);
	data_init(fractal);
}
