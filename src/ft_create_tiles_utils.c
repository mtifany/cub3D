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

void	ft_fill_tile(char **map, int y, int x, t_game *game)
{
	t_tile	**tiles;

	tiles = game->tiles;
	tiles[y][x].x = x * 64;
	tiles[y][x].y = y * 64;
	if (map)
		tiles[y][x].type = map[y][x];
	else
		tiles[y][x].type = ' ';
	if (map && (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
		|| map[y][x] == 'W'))
	{
		tiles[y][x].x = tiles[y][x].x + 32;
		tiles[y][x].y = tiles[y][x].y + 32;
		game->player.tile = tiles[y][x];
	}
}

void	ft_fill_tiles(char **map, t_game *game)
{
	int	x;
	int	y;
	int	str_width;

	y = 0;
	while (y < game->hightpx / 64)
	{
		x = 0;
		str_width = (int)ft_strlen(map[y]) - 1;
		while (x < str_width)
		{
			ft_fill_tile(map, y, x, game);
			x++;
		}
		while (x < game->widthpx / 64)
		{
			ft_fill_tile(NULL, y, x, game);
			x++;
		}
		y++;
	}
}

static t_tile	**ft_alloc_widthoftiles(char **map, t_tile **tiles, int len)
{
	int	i;

	i = 0;
	while (map[i])
	{
		tiles[i] = (t_tile *)malloc(sizeof(t_tile) * (len));
		if (!tiles[i])
		{
			while (i)
			{
				free(tiles[--i]);
			}
			free(tiles);
			return (NULL);
		}
		i++;
	}
	return (tiles);
}

static int	ft_get_mapwidth(char **map)
{
	size_t	width;
	size_t	max_width;

	max_width = 0;
	while (*map)
	{
		width = ft_strlen(*map) - 1;
		if ((width > max_width))
		{
			max_width = width;
		}
		map++;
	}
	return ((int)max_width);
}

t_tile	**ft_alloc_tiles(char **map, t_game *game)
{
	t_tile	**tiles;
	int		i;
	int		len;

	i = 0;
	while (map[i])
		i++;
	game->hightpx = 64 * i;
	tiles = malloc(sizeof(t_tile *) * (i + 1));
	if (!tiles)
		return (NULL);
	tiles[i] = NULL;
	len = ft_get_mapwidth(map);
	game->widthpx = 64 * (len);
	return (ft_alloc_widthoftiles(map, tiles, len));
}
