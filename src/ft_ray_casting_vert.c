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

static double	ft_find_first_x_vert_inters_set_d_x_and_texture(
		t_game *game, double *d_x, t_texture *texture)
{
	double	x;

	if (cos(game->ray.alpha) >= 0)
	{
		x = floor(game->player.tile.x / 64.0) * 64 + 64;
		*d_x = 64;
		*texture = game->textures.ea;
	}
	else
	{
		x = floor(game->player.tile.x / 64.0) * 64 - 0.0000001;
		*d_x = -64;
		*texture = game->textures.we;
	}
	return (x);
}

int	ft_ray_casting_vert1(t_game *game, t_ray *ray, double x, double y)
{
	if (ft_is_grid_wall(game->tiles, (int)floor(y / 64), (int)floor(x / 64)))
	{
		ray->x = x;
		ray->y = y;
		ray->x_texture = (int) y % 64;
		if (cos(ray->alpha) < 0)
			ray->x_texture = 64 - (int) y % 64 - 1;
		ray->dist = sqrt(pow((game->player.tile.x - x), 2)
				+ pow((game->player.tile.y - y), 2)) * cos(ray->beta);
		return (1);
	}
	return (0);
}

t_ray	ft_ray_casting_vert(t_game *game, t_ray ray)
{
	double	x;
	double	y;
	double	d_x;
	double	d_y;

	if (ray.i == 250)
		ray.x = -1;
	x = ft_find_first_x_vert_inters_set_d_x_and_texture(
			game, &d_x, &(ray.texture));
	y = game->player.tile.y + ((game->player.tile.x - x) * tan(ray.alpha));
	d_y = 64 * tan(ray.alpha);
	if ((d_y > 0 && cos(ray.alpha) > 0 && sin(ray.alpha) > 0)
		|| (d_y < 0 && cos(ray.alpha) > 0 && sin(ray.alpha) < 0))
		d_y = -d_y;
	while (x >= 0 && y >= 0 && x < game->widthpx && y < game->hightpx)
	{
		if (ft_ray_casting_vert1(game, &ray, x, y))
			return (ray);
		x += d_x;
		y += d_y;
	}
	ray.dist = -1;
	return (ray);
}
