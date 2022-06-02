/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*                                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 23:43:39 by                   #+#    #+#             */
/*   Updated: 2022/01/25 14:33:20 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3.h"

static int	ft_is_to_reset(
		int x_texture, int wall_hght, int *count, double *y1)
{
	if (x_texture < 0 || wall_hght < 0)
	{
		*count = 0;
		*y1 = 0;
		return (1);
	}
	return (0);
}

int	ft_texture_color(t_texture texture, int x_texture, int wall_hght,
							t_color *color)
{
	static double	y1;
	static int		count;
	double			d_y;
	int				y;

	if (ft_is_to_reset(x_texture, wall_hght, &count, &y1))
		return (1);
	if (!y1)
		y1 = (64 - texture.hight) / 3.0 * 2.0;
	d_y = texture.hight / (double) wall_hght;
	y = (int) y1;
	y1 = y1 + d_y;
	if (count < wall_hght)
	{
		color->r = texture.addr[4 * x_texture + texture.line_size * y + 0];
		color->g = texture.addr[4 * x_texture + texture.line_size * y + 1];
		color->b = texture.addr[4 * x_texture + texture.line_size * y + 2];
		color->t = texture.addr[4 * x_texture + texture.line_size * y + 3];
		count++;
		return (0);
	}
	count = 0;
	y1 = 0;
	return (1);
}

void	ft_fill_floor(int y, int x, t_game *game)
{
	t_panel	panel;

	panel = game->panel;
	while (y < game->scrn_hght)
	{
		panel.addr[4 * x + panel.line_size * y + 0] = game->fcolor.b;
		panel.addr[4 * x + panel.line_size * y + 1] = game->fcolor.g;
		panel.addr[4 * x + panel.line_size * y + 2] = game->fcolor.r;
		panel.addr[4 * x + panel.line_size * y + 3] = game->fcolor.t;
		y++;
	}
}

void	ft_fill_sky(int max_y, int x, t_game *game)
{
	int		y;
	t_panel	panel;

	panel = game->panel;
	y = 0;
	while (y < max_y)
	{
		panel.addr[4 * x + panel.line_size * y + 0] = game->scolor.b;
		panel.addr[4 * x + panel.line_size * y + 1] = game->scolor.g;
		panel.addr[4 * x + panel.line_size * y + 2] = game->scolor.r;
		panel.addr[4 * x + panel.line_size * y + 3] = game->scolor.t;
		y++;
	}
}
