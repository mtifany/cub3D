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

void	ft_read_map3(char *s, t_game *game)
{
	char	*tmp;

	if (!game->map_str)
		game->map_str = ft_substr(s, 0, ft_strlen(s));
	else
	{
		tmp = ft_strjoin(game->map_str, s);
		free(game->map_str);
		game->map_str = tmp;
	}
}

void	ft_read_map2(char *s, int fd, t_game *game)
{
	while (s)
	{
		game->map_line_count++;
		if ((!s) || !s[0] || s[0] == '\n' )
		{
			free(s);
			ft_error_and_exit("Wrong string in map!\n", game);
		}
		if (game->map_line_len < (int)ft_strlen(s))
		{
			game->map_line_len = (int) ft_strlen(s);
			if (s[ft_strlen(s) - 1] == '\n')
				game->map_line_len -= 1;
		}
		ft_read_map3(s, game);
		free(s);
		s = get_next_line(fd);
	}
	free(s);
	close(fd);
}

void	ft_read_empty(char *s, int fd, t_game *game)
{
	while (s)
	{
		if ((!s) || !s[0])
		{
			free(s);
			ft_error_and_exit("string readin1g problem.\n", game);
		}
		if (s[0] != '\n' && ft_check_s(s, game))
		{
			ft_read_map2(s, fd, game);
			break ;
		}
		free(s);
	s = get_next_line(fd);
	}
}

void	ft_read_args(char *s, int fd, t_game *game)
{
	s = get_next_line(fd);
	while (s)
	{
		if (game->so_file && game->no_file && game->ea_file && \
		game->we_file && game->fcolor.temp && game->scolor.temp)
		{
			ft_read_empty(s, fd, game);
			break ;
		}
		if ((!s) || !s[0])
		{
			free(s);
			ft_error_and_exit("string reading problem.\n", game);
		}
		ft_check_str(s, game);
		free(s);
		s = get_next_line(fd);
	}
	if (!game->so_file && !game->no_file && !game->ea_file && \
		!game->we_file && !game->fcolor.temp && !game->scolor.temp)
	{
		free(s);
		ft_error_and_exit("string reading problem.\n", game);
	}
}

char	**reader(char *path, t_game *game)
{
	int		fd;
	char	*s;
	char	**map;
	int		i;

	i = 0;
	ft_check_mappath(path, game);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_error_and_exit("openFile is empty or it can not be read.\n", game);
	game->fcolor.temp = 0;
	game->scolor.temp = 0;
	game->map_line_len = 0;
	game->map_line_count = 0;
	s = "";
	ft_read_args(s, fd, game);
	map = ft_make_map(game);
	if (ft_check_map(map, game, i) != 0)
	{
		ft_free_map(map);
		ft_error_and_exit("Error while cheking map!", game);
	}
	return (map);
}
