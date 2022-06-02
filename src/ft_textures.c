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

static t_texture	ft_create_texture(t_game *game, char *path)
{
	t_texture	texture;

	texture.ref = mlx_xpm_file_to_image(
			game->mlx, path, &(texture.width), &(texture.hight));
	if (texture.ref)
		texture.addr = mlx_get_data_addr(texture.ref, &(texture.bit_per_px),
				&(texture.line_size), &(texture.end));
	return (texture);
}

void	ft_init_textures(t_game *game)
{
	game->textures.no = ft_create_texture(game, game->no_file);
	game->textures.so = ft_create_texture(game, game->so_file);
	game->textures.we = ft_create_texture(game, game->we_file);
	game->textures.ea = ft_create_texture(game, game->ea_file);
	if (!(game->textures.no.ref) || !(game->textures.so.ref)
		|| !(game->textures.ea.ref) || !(game->textures.we.ref))
	{
		ft_show_error_and_destroy_game(game, "Error trying to init textures\n");
	}
}
