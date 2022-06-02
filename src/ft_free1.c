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

void	ft_check_linecount_and_exit(t_game *game, int line_count)
{
	if (!line_count)
		ft_error_and_exit("File is empty or it can not be read.\n", game);
	if (line_count == 1 || line_count == 2)
		ft_error_and_exit("Map is too small.\n", game);
}

void	ft_show_error_and_destroy_game(t_game *game, char *s)
{
	(void)(game);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(s, 2);
	exit(1);
}

int	ft_close(t_game *game)
{
	ft_destroy_game(game);
	exit(0);
}

void	ft_destroy_textures(void *mlx, t_textures textures)
{
	if (textures.no.ref)
		mlx_destroy_image(mlx, textures.no.ref);
	if (textures.so.ref)
		mlx_destroy_image(mlx, textures.so.ref);
	if (textures.we.ref)
		mlx_destroy_image(mlx, textures.we.ref);
	if (textures.ea.ref)
		mlx_destroy_image(mlx, textures.ea.ref);
}

void	ft_destroy_game(t_game *game)
{
	ft_destroy_textures(game->mlx, game->textures);
	if (game->panel.ref)
		mlx_destroy_image(game->mlx, game->panel.ref);
	mlx_destroy_window(game->mlx, game->window);
	free(game->no_file);
	free(game->so_file);
	free(game->ea_file);
	free(game->we_file);
	ft_free_tiles(game->tiles);
	free(game);
}
