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

static t_game	*ft_create_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
	{
		ft_error_and_exit("Can not allocate memory in main for the game.\n",
			game);
	}
	ft_bzero(game, sizeof(t_game));
	game->scrn_wdth = 1180;
	game->scrn_hght = 800;
	game->camera_angl = 0.0;
	game->view_angle = 66.0;
	game->angle_between_rays = game->view_angle / game->scrn_wdth;
	game->dist_to_scrn = (int)
		(game->scrn_wdth / 2.0 / tan(game->view_angle / 2 * 0.0174532925));
	game->fcolor.r = -1;
	game->fcolor.g = -1;
	game->fcolor.b = -1;
	game->fcolor.t = 0;
	game->scolor.r = -1;
	game->scolor.g = -1;
	game->scolor.b = -1;
	game->scolor.t = 0;
	return (game);
}

void	ft_set_player_pos(t_game *game)
{
	if (game->player.tile.type == 'W')
		game->camera_angl = 0.0;
	else if (game->player.tile.type == 'N')
		game->camera_angl = 90.0;
	else if (game->player.tile.type == 'E')
		game->camera_angl = 180.0;
	else if (game->player.tile.type == 'S')
		game->camera_angl = 270.0;
}

int	ft_key_esc(int key, void *g)
{
	t_game	*game;

	game = (t_game *)g;
	if (key == 53)
	{
		ft_destroy_game(game);
		exit(0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	char		**map;
	t_game		*game;

	if (argc < 2)
		return (1);
	game = ft_create_game();
	map = reader(*(argv + 1), game);
	ft_create_tiles_from_map(map, game);
	ft_free_map(map);
	ft_set_player_pos(game);
	game->mlx = mlx_init();
	game->window = mlx_new_window(
			game->mlx, game->scrn_wdth, game->scrn_hght, "cub3D");
	mlx_hook(game->window, 17, 0, ft_close, game);
	ft_init_textures(game);
	game->panel = ft_init_panel(game);
	ft_rays_casting(game);
	mlx_key_hook(game->window, ft_key_esc, (void *)game);
	mlx_hook(game->window, 2, 0, ft_key_press, (void *)game);
	mlx_loop(game->mlx);
	return (0);
}
