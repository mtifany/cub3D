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

static int	ft_get_wall_hght_adjust_text_hght(
		t_game *game, t_ray ray, t_texture *texture)
{
	unsigned long	wall_hght;

	wall_hght = (int) ceil(64 / ray.dist * game->dist_to_scrn);
	if (wall_hght > 2147483647)
		wall_hght = 2147483647;
	if ((int)wall_hght > game->panel.hight)
	{
		texture->hight = (int)(texture->hight
				- ((int)wall_hght - game->panel.hight)
				/ (double) wall_hght * texture->hight);
		wall_hght = game->panel.hight;
	}
	return ((int)wall_hght);
}

void	ft_fill_drawing(t_game *game, t_ray ray)
{
	int			wall_hght;
	int			y;
	int			x;
	t_color		color;
	t_texture	texture;

	texture = ray.texture;
	wall_hght = ft_get_wall_hght_adjust_text_hght(game, ray, &texture);
	y = (int)((game->scrn_hght / 3.0 - wall_hght / 3.0) * 2.0);
	x = game->ray.i;
	ft_fill_sky(y, x, game);
	while (y < game->scrn_hght
		&& !ft_texture_color(texture, ray.x_texture, wall_hght, &color))
	{
		game->panel.addr[4 * x + game->panel.line_size * y + 0] = color.r;
		game->panel.addr[4 * x + game->panel.line_size * y + 1] = color.g;
		game->panel.addr[4 * x + game->panel.line_size * y + 2] = color.b;
		game->panel.addr[4 * x + game->panel.line_size * y + 3] = color.t;
		y++;
	}
	ft_texture_color(texture, -1, wall_hght, &color);
	ft_fill_floor(y, x, game);
}
