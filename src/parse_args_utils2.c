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

int	ft_parse(const char *str)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	if (!str)
		return (-1);
	while (str[i] == ' ')
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
		if ((res > 255))
			return (-1);
	}
	while (str[i] == ' ')
		i++;
	if (str[i] && str[i] != '\n')
		return (-1);
	return (res);
}

void	ft_check_str(char *s, t_game *game)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		while (s[i] == ' ' && s[i + 1])
			i++;
		if (s[i] == 'F' || s[i] == 'C')
		{
			fill_color((s + i + 1), game, s[i], s);
			break ;
		}
		if ((s[i] == 'N' && s[i + 1] == 'O') || (s[i] == 'S' && s[i + 1] \
		=='O') || (s[i] == 'W' && s[i + 1] == 'E') || \
		(s[i] == 'E' && s[i + 1] == 'A'))
		{
			fill_path((s + i + 2), game, s[i]);
			break ;
		}
		if (s[i] != '\n')
		{
			ft_error_and_exit("Not empty string with information\n", game);
			break ;
		}
	}
}

void	ft_check_mappath(char *path, t_game *game)
{
	int	len;

	len = (int) ft_strlen(path);
	if (len < 4 || ft_strncmp(path + len - 4, ".cub", 4))
		ft_error_and_exit("Path is not valid.\n", game);
}

int	ft_check_s(char *s, t_game *game)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (new_strchr("NSWE01 \n", s[i]) == -1)
		{
			free(s);
			ft_error_and_exit("Not empty string\n", game);
		}
	}
	return (1);
}
