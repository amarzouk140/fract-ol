/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayman_marzouk <ayman_marzouk@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 23:12:19 by ayman_marzo       #+#    #+#             */
/*   Updated: 2024/02/09 13:58:40 by ayman_marzo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->connect, fractal->img.img_ptr);
	mlx_destroy_window(fractal->connect, fractal->window);
	free(fractal->connect);
	exit(0);
}

void	colour_shift(t_fractal *fract)
{
	static int colours[] = {WHITE, PASTELPINK, GREEN, BLUE, MAGENTA, LIME, ORANGE, PURPLE, AQUA, PINK, ELECTRIC, LIGHTENING, LAVA, YELLOW, PASTELYELLOW};
	static int colour_index = 0;

	colour_index = (colour_index + 1) % (sizeof(colours) / sizeof(colours[0]));
	fract->current_colour = colours[colour_index];
	fractal_render(fract);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == K_ESC)
		close_handler(fractal);
	if (keysym == K_LEFT)
		fractal->shift_x += (0.5 * fractal->zoom);
	else if (keysym == K_RIGHT)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if (keysym == K_UP)
		fractal->shift_y -= (0.5 * fractal->zoom);
	else if (keysym == K_DOWN)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keysym == Q)
		fractal->iterations += 10;
	else if (keysym == W)
		fractal->iterations -= 10;
	if (keysym == R)
		data_init(fractal);
	if (keysym == 69)
		fractal->zoom *= 0.95;
	else if (keysym == 78)
		fractal->zoom *= 1.05;
	if (keysym == SPACE)
		fractal->flag = !fractal->flag;
	if (keysym == 8)
		colour_shift(fractal);
	fractal_render(fractal);
	return (0);
}

static void	update_zoom_center(t_fractal *fractal, int mouse_x, int mouse_y)
{
	fractal->shift_x = map(mouse_x, -2, +2, WIDTH) * fractal->zoom;
	fractal->shift_y = map(mouse_y, +2, -2, HEIGHT) * fractal->zoom;
}

int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	(void)x;
	(void)y;
	if (button == 4)
	{
		fractal->zoom *= 0.95;
		update_zoom_center(fractal, x, y);
	}
	else if (button == 5)
	{
		fractal->zoom *= 1.05;
		update_zoom_center(fractal, x, y);
	}
	fractal_render(fractal);
	return (0);
}

int	julia_track(int x, int y, t_fractal *fractal)
{
	if (!ft_strcmp(fractal->name, "julia"))
	{
		if (!fractal->flag)
		{
			fractal->julia_x = (map(x, -2, +2, WIDTH) * fractal->zoom)
				+ fractal->shift_x;
			fractal->julia_y = (map(y, +2, -2, HEIGHT) * fractal->zoom)
				+ fractal->shift_y;
			fractal_render(fractal);
		}
	}
	return (0);
}
