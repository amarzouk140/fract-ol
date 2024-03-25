/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarzouk <amarzouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:43:32 by amarzouk          #+#    #+#             */
/*   Updated: 2024/03/25 10:47:43 by amarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_complex	abs_complex(t_complex z)
{
	t_complex	result;

	result.x = fabs(z.x);
	result.y = fabs(z.y);
	return (result);
}

static void	init_pixel_params(t_pixel_params *params, int x, int y,
		t_fractal *fractal)
{
	params->x = x;
	params->y = y;
	params->fractal = fractal;
	params->z = (t_complex){0, 0};
	params->c = (t_complex){0, 0};
}

static void	setup_fractal(t_pixel_params *params)
{
	params->z.x = map(params->x, -2, +2, WIDTH) * params->fractal->zoom
		+ params->fractal->shift_x;
	params->z.y = map(params->y, +2, -2, HEIGHT) * params->fractal->zoom
		+ params->fractal->shift_y;
	if (!ft_strcmp(params->fractal->name, "burning_ship"))
	{
		params->c.x = params->z.x;
		params->c.y = params->z.y;
		params->z.x = 0;
		params->z.y = 0;
	}
	else if (!ft_strcmp(params->fractal->name, "julia"))
	{
		params->c.x = params->fractal->julia_x;
		params->c.y = params->fractal->julia_y;
	}
	else
	{
		params->c.x = params->z.x;
		params->c.y = params->z.y;
		params->z.x = 0;
		params->z.y = 0;
	}
}

static void	process_pixel(t_pixel_params *params)
{
	int	i;
	int	color;

	i = 0;
	while (i < params->fractal->iterations)
	{
		if (!ft_strcmp(params->fractal->name, "burning_ship"))
		{
			params->z = abs_complex(params->z);
		}
		params->z = sum_complex(square_complex(params->z), params->c);
		if ((params->z.x * params->z.x) + (params->z.y
				* params->z.y) > params->fractal->escape_value)
		{
			color = get_psychedelic_color(i, params->fractal->iterations);
			my_pixel_put(params->x, params->y, &params->fractal->img, color);
			return ;
		}
		i++;
	}
	my_pixel_put(params->x, params->y, &params->fractal->img, BLACK);
}

void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_pixel_params	params;

	init_pixel_params(&params, x, y, fractal);
	setup_fractal(&params);
	process_pixel(&params);
}
