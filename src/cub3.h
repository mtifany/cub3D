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

#ifndef CUB3_H
# define CUB3_H

# include <unistd.h>
# include <stdio.h>
# include "../minilibx_opengl/mlx.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	t;
	int	temp;
}	t_color;

typedef struct s_panel
{
	void	*ref;
	int		width;
	int		hight;
	int		bit_per_px;
	int		line_size;
	int		end;
	char	*addr;
}	t_panel;

typedef struct s_texture
{
	void	*ref;
	int		width;
	int		hight;
	int		bit_per_px;
	int		line_size;
	int		end;
	char	*addr;
}	t_texture;

typedef struct s_textures
{
	t_texture	no;
	t_texture	so;
	t_texture	we;
	t_texture	ea;
}	t_textures;

typedef struct s_tile
{
	char	type;
	int		x;
	int		y;
	int		isv;
	int		isup_or_left;
	int		freeze;
}	t_tile;

typedef struct s_player
{
	t_tile	tile;
	void	*img2;
}	t_player;

typedef struct s_ray
{
	double		x;
	double		y;
	int			i;
	double		alpha;
	double		beta;
	int			x_texture;
	t_texture	texture;
	double		dist;
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_panel		panel;
	t_color		scolor;
	t_color		fcolor;
	t_tile		**tiles;
	t_player	player;
	t_textures	textures;
	t_ray		ray;
	int			widthpx;
	int			hightpx;
	int			collectibles;
	int			players;
	int			exits;
	int			scrn_hght;
	int			scrn_wdth;
	int			map_width;
	int			map_height;
	int			map_line_len;
	int			map_line_count;
	double		camera_angl;
	double		angle_between_rays;
	double		view_angle;
	int			dist_to_scrn;
	char		*no_file;
	char		*so_file;
	char		*we_file;
	char		*ea_file;
	char		*map_str;

}	t_game;

int		ft_texture_color(t_texture texture, int x_texture, int wall_hght, \
		t_color *color);
void	ft_fill_floor(int y, int x, t_game *game);
void	ft_fill_sky(int max_y, int x, t_game *game);
int		ft_key_press(int keycode, void *vgame);
void	ft_set_first_ray_data(t_game *game, double *d_angle);
int		ft_move_rot(int is_right, t_game *game);
void	ft_move(int (*f)(int, t_game *), int is_up_right, t_game *game);
int		ft_rays_casting(t_game *game);
t_ray	ft_ray_casting_vert(t_game *game, t_ray ray);
t_ray	ft_ray_casting_hor(t_game *game, t_ray ray);
void	ft_fill_drawing(t_game *game, t_ray ray);
void	ft_init_textures(t_game *game);
void	ft_destroy_textures(void *mlx, t_textures textures);
void	ft_destroy_game(t_game *game);
int		ft_player_move(int key, void *g);
int		ft_move_player_down(t_game *game);
int		ft_move_player_left(t_game *game);
int		ft_move_player_right(t_game *game);
int		ft_move_player_up(t_game *game);
void	ft_free_trying_tofill_tiles(t_game *game, char **map, char *error);
int		ft_update(void *g);
void	ft_free_map(char **map);
void	ft_free_tiles(t_tile **tiles);
void	ft_error_after_secondread(
			int i, int line_count, char **map, t_game *game);
void	ft_error_and_exit(char *string, t_game *game);
int		ft_close(t_game *game);
char	**ft_read_map(char *path, t_game *game);
t_tile	**ft_create_tiles_from_map(char **map, t_game *game);
char	*get_next_line(int fd);
int		ft_check_type(char **map, int y, int x, t_game *game);
int		ft_check_ifallelements_avail(t_game *game, char **map);
void	ft_check_mappath(char *path, t_game *game);
void	ft_check_mapwidth(int fd, char *s, size_t *width, t_game *game);
int		ft_mine_move(t_game *game, int x, int y);
void	ft_show_error_and_destroy_game(t_game *game, char *s);
int		ft_mine_moveg(t_game *game, int x, int y);
void	*ft_mine_sprite(t_game *game);
int		ft_ismine_moved(t_game *game, int x, int y, t_tile tile);
int		ft_mine_movev(t_game *game, int x, int y);
void	ft_check_linecount_and_exit(t_game *game, int linecount);
t_panel	ft_init_panel(t_game *game);
char	**reader(char *path, t_game *game);
int		ft_parse(const char *str);
int		new_strchr(const char *s, int c);
void	fill_color(char *s, t_game *game, char c, char *str);
void	fill_path(char *s, t_game *game, char c);
void	ft_check_str(char *s, t_game *game);
int		ft_check_map(char **map, t_game *game, int i);
char	**ft_make_map(t_game *game);
char	**ft_fill_map(t_game *game, char **temp, char **map);
t_tile	**ft_alloc_tiles(char **map, t_game *game);
void	ft_fill_tiles(char **map, t_game *game);
int		ft_move_left_right(int is_right, t_game *game);
int		ft_move_up_down(int is_up, t_game *game);
int		ft_is_grid_wall(t_tile **tiles, int y, int x);
int		ft_check_s(char *s, t_game *game);

#endif
