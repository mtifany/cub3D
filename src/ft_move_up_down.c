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

int	ft_move_up(t_game *game, double d_x, double d_y)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < 50)
	{
		x = game->player.tile.x + (int)(d_x * i);
		y = game->player.tile.y - (int)(d_y * i);
		if (game->tiles[y / 64][x / 64].type == '1')
			return (1);
		i++;
	}
	x = game->player.tile.x + (int)(d_x * 10);
	y = game->player.tile.y - (int)(d_y * 10);
	game->tiles[game->player.tile.y / 64][game->player.tile.x / 64].type = '0';
	game->tiles[y / 64][x / 64].type = game->player.tile.type;
	game->player.tile.type = game->player.tile.type;
	game->player.tile.x = x;
	game->player.tile.y = y;
	return (0);
}

int	ft_move_down(t_game *game, double d_x, double d_y)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < 50)
	{
		x = game->player.tile.x - (int)(d_x * i);
		y = game->player.tile.y + (int)(d_y * i);
		if (game->tiles[y / 64][x / 64].type == '1')
			return (1);
		i++;
	}
	x = game->player.tile.x - (int)(d_x * 10);
	y = game->player.tile.y + (int)(d_y * 10);
	game->tiles[game->player.tile.y / 64][game->player.tile.x / 64].type = '0';
	game->tiles[y / 64][x / 64].type = game->player.tile.type;
	game->player.tile.type = game->player.tile.type;
	game->player.tile.x = x;
	game->player.tile.y = y;
	return (0);
}

int	ft_move_up_down(int is_up, t_game *game)
{
	double	d_x;
	double	d_y;

	d_x = cos(game->camera_angl * 0.0174532925);
	d_y = sin(game->camera_angl * 0.0174532925);
	if (is_up)
	{
		if (ft_move_up(game, d_x, d_y))
			return (1);
	}
	else
	{
		if (ft_move_down(game, d_x, d_y))
			return (1);
	}
	return (0);
}
