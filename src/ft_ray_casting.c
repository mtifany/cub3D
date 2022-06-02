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

static void	ft_ray_casting(t_game *game)
{
	t_ray	ray1;
	t_ray	ray2;

	ray1 = ft_ray_casting_hor(game, game->ray);
	ray2 = ft_ray_casting_vert(game, game->ray);
	if (ray1.dist > 0 && (ray2.dist < 0 || ray2.dist > ray1.dist))
	{
		game->ray = ray1;
	}
	else
	{
		game->ray = ray2;
	}
	ft_fill_drawing(game, game->ray);
}

void	ft_set_first_ray_data(t_game *game, double *d_angle)
{
	game->ray.alpha = (game->camera_angl + game->view_angle / 2) * 0.0174532925;
	game->ray.beta = game->view_angle / 2 * 0.0174532925;
	*d_angle = game->angle_between_rays * 0.0174532925;
}

int	ft_rays_casting(t_game *game)
{
	double	d_angle;
	int		i;

	ft_bzero(game->panel.addr, game->panel.width * game->panel.hight * 4);
	ft_set_first_ray_data(game, &d_angle);
	i = 0;
	while (i < game->scrn_wdth)
	{
		game->ray.i = i;
		ft_ray_casting(game);
		game->ray.alpha = game->ray.alpha - d_angle;
		game->ray.beta = game->ray.beta - d_angle;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->panel.ref, 0, 0);
	return (0);
}
