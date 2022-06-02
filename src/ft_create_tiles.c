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

t_tile	**ft_create_tiles_from_map(char **map, t_game *game)
{
	game->tiles = ft_alloc_tiles(map, game);
	if (!(game->tiles))
	{
		free(game);
		ft_free_map(map);
		ft_error_and_exit(
			"Can not allocate memory for tiles\n", game);
	}
	ft_fill_tiles(map, game);
	return (game->tiles);
}
