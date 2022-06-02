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

int	int_strchr(const char *s, int c)
{
	while (*s && *s != c)
		s++;
	if (*s == c)
		return (1);
	return (0);
}

int	new_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

char	**ft_fill_map(t_game *game, char **temp, char **map)
{
	int		i;
	int		j;

	i = -1;
	while (temp[++i])
	{
		map[i] = malloc(sizeof(char) * game->map_line_len + 2);
		if (!map[i])
		{
			ft_free_map(temp);
			ft_error_and_exit("wrong symbols on map!.\n", game);
		}
		j = -1;
		while (++j < game->map_line_len)
		{
			if (j < (int)ft_strlen(temp[i]))
				map[i][j] = temp[i][j];
			else
				map[i][j] = ' ';
		}
		map[i][j] = '\n';
		map[i][j + 1] = '\0';
	}
	map[i] = NULL;
	return (map);
}

char	**ft_make_map(t_game *game)
{
	char	**temp;
	char	**map;

	temp = ft_split(game->map_str, '\n');
	free(game->map_str);
	map = malloc(sizeof(char *) * (game->map_line_count + 1));
	if (!map || !temp)
	{
		ft_free_map(temp);
		ft_error_and_exit("Error while allocating map!\n", game);
	}
	map = ft_fill_map(game, temp, map);
	ft_free_map(temp);
	return (map);
}

int	ft_check_map(char **map, t_game *game, int i)
{
	int	j;
	int	flag;

	i = -1;
	flag = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (new_strchr("NSWE01 \n", map[i][j]) == -1 || \
			(!int_strchr(map[i], '0') && !int_strchr(map[i], '1')))
				return (-1);
			if (new_strchr("NSWE", map[i][j]) >= 0)
				flag++;
			if ((map[i][j] == '0' || map[i][j] >= 60) && (i == 0 \
			|| i == game->map_line_count || j == 0 || j == game->map_line_len))
				return (-1);
			if ((map[i][j] == '0' || map[i][j] >= 60) && (map[i + 1][j] == \
			' ' || map[i][j + 1] == ' ' || map[i - 1][j] == ' ' || map[i][j - \
			1] == ' '))
				return (-1);
		}
	}
	return (flag);
}
