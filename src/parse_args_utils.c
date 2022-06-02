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

void	ft_fill_f(t_game *game, char **arr, char *str)
{
	game->fcolor.r = ft_parse(arr[0]);
	game->fcolor.g = ft_parse(arr[1]);
	game->fcolor.b = ft_parse(arr[2]);
	if (game->fcolor.r < 0 || game->fcolor.g < 0 || game->fcolor.b < 0 || \
		game->fcolor.temp > 0)
	{
		free(str);
		ft_error_and_exit("wrong color argument!\n", game);
	}
	game->fcolor.temp = 1;
}

void	ft_fill_s(t_game *game, char **arr, char *str)
{
	game->scolor.r = ft_parse(arr[0]);
	game->scolor.g = ft_parse(arr[1]);
	game->scolor.b = ft_parse(arr[2]);
	if (game->scolor.r < 0 || game->scolor.g < 0 || game->scolor.b < 0 || \
		game->scolor.temp > 0)
	{
		free(str);
		ft_error_and_exit("wrong color argument!\n", game);
	}
	game->scolor.temp = 1;
}

void	fill_color(char *s, t_game *game, char c, char *str)
{
	char	**arr;

	arr = ft_split(s, ',');
	if (!arr[0] || !arr[1] || !arr[2] || arr[3])
	{
		ft_free_map(arr);
		ft_error_and_exit("Wrong color arguments\n", game);
	}
	if (c == 'F')
		ft_fill_f(game, arr, str);
	else
		ft_fill_s(game, arr, str);
	ft_free_map(arr);
}

void	fill_path2(char *s, t_game *game, char c, int i)
{
	if (c == 'E')
	{
		if (game->ea_file)
		{
			free(s);
			ft_error_and_exit("Second NO argument\n", game);
		}
		game->ea_file = ft_substr(s, i, ft_strlen(s) - i -1);
	}
	if (c == 'W')
	{
		if (game->we_file)
		{
			free(s);
			ft_error_and_exit("Second NO argument\n", game);
		}
		game->we_file = ft_substr(s, i, ft_strlen(s) - i -1);
	}
}

void	fill_path(char *s, t_game *game, char c)
{
	int	i;

	i = 0;
	while (s[i] == ' ' && s[i + 1])
		i++;
	if (c == 'N')
	{
		if (game->no_file)
		{
			ft_error_and_exit("Second NO argument\n", game);
		}
		game->no_file = ft_substr(s, i, ft_strlen(s) - i - 1);
	}
	else if (c == 'S')
	{
		if (game->so_file)
		{
			free(s);
			ft_error_and_exit("Second NO argument\n", game);
		}
		game->so_file = ft_substr(s, i, ft_strlen(s) - i - 1);
	}
	else
		fill_path2(s, game, c, i);
}
