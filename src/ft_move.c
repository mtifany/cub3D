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

int	ft_move_rot(int is_right, t_game *game)
{
	if (is_right)
	{
		game->camera_angl = game->camera_angl - 10.0;
		if (game->camera_angl < 0)
			game->camera_angl = 360.0 + game->camera_angl;
	}
	else
	{
		game->camera_angl = game->camera_angl + 10.0;
		if (game->camera_angl > 360.0)
			game->camera_angl = game->camera_angl - 360.0;
	}
	return (0);
}

void	ft_move(int (*f)(int, t_game *), int is_up_right, t_game *game)
{
	if (!f(is_up_right, game))
	{
		ft_rays_casting(game);
	}
}

int	ft_key_press(int keycode, void *vgame)
{
	static int	frame = 5;
	t_game		*game;

	game = (t_game *)vgame;
	frame = 0;
	if (keycode == 124)
		ft_move(ft_move_rot, 1, game);
	if (keycode == 123)
		ft_move(ft_move_rot, 0, game);
	if (keycode == 13 || keycode == 126)
		ft_move(ft_move_up_down, 1, game);
	if (keycode == 1 || keycode == 125)
		ft_move(ft_move_up_down, 0, game);
	if (keycode == 0)
		ft_move(ft_move_left_right, 1, game);
	if (keycode == 2)
		ft_move(ft_move_left_right, 0, game);
	return (1);
}
