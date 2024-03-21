/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayman_marzouk <ayman_marzouk@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 21:15:10 by ayman_marzo       #+#    #+#             */
/*   Updated: 2024/03/22 00:35:44 by ayman_marzo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int main(int ac, char **av) {
    t_fractal fractal;

    if (ac < 2) {
        ft_printf("Usage: %s [fractal] [options]\n", av[0]);
        ft_printf("Fractals:\n - mandelbrot\n - julia <real_part> <imaginary_part>\n - burning_ship\n");
        return (1);
    }

    fractal.name = av[1];
    if (!ft_strcmp(fractal.name, "mandelbrot") || 
        (!ft_strcmp(fractal.name, "julia") && ac == 4) ||
        (!ft_strcmp(fractal.name, "burning_ship") && ac == 2)) {

        if (!ft_strcmp(fractal.name, "julia")) {
            fractal.julia_x = atodbl(av[2]);
            fractal.julia_y = atodbl(av[3]);
        }
        fractal_init(&fractal);
        fractal_render(&fractal);
        mlx_loop(fractal.connect);
    } else {
        ft_printf("Invalid fractal or incorrect number of arguments.\n");
        ft_printf("Usage for Julia set: %s julia <real_part> <imaginary_part>\n", av[0]);
        ft_printf("Usage for Mandelbrot set: %s mandelbrot\n", av[0]);
        ft_printf("Usage for Burning Ship set: %s burning_ship\n", av[0]);
    }

    return (0);
}
