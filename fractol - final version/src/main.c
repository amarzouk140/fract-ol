/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzouk <amarzouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 21:15:10 by ayman_marzo       #+#    #+#             */
/*   Updated: 2024/03/25 10:04:13 by amarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_list(char **av, int i)
{
	if (i == 1)
	{
		ft_printf("Usage: %s [fractal] [options]\n", av[0]);
		ft_printf("Fractals:\n - mandelbrot\n - burning_ship\n");
		ft_printf("- julia <real_part> <imaginary_part> \n");
		exit(1);
	}
	else if (i == 2)
	{
		ft_printf("Invalid fractal or incorrect number of arguments.\n");
		ft_printf("Usage for Julia set:%s julia <real_part> <imaginary_part>\n",
			av[0]);
		ft_printf("Usage for Mandelbrot set: %s mandelbrot\n", av[0]);
		ft_printf("Usage for Burning Ship set: %s burning_ship\n", av[0]);
		exit(0);
	}
}

int	main(int ac, char **av)
{
	t_fractal	fractal;

	if (ac < 2)
		print_list(av, 1);
	fractal.name = av[1];
	if (!ft_strcmp(fractal.name, "mandelbrot") || (!ft_strcmp(fractal.name,
				"julia") && ac == 4) || (!ft_strcmp(fractal.name,
				"burning_ship") && ac == 2))
	{
		if (!ft_strcmp(fractal.name, "julia"))
		{
			fractal.julia_x = atodbl(av[2]);
			fractal.julia_y = atodbl(av[3]);
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.connect);
	}
	else
		print_list(av, 2);
	return (0);
}
