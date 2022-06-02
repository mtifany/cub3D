NAME = cub3D
DIR_OBJ = obj
SRC = main.c get_next_line.c get_next_line_utils.c ft_free.c ft_free1.c\
 ft_create_tiles.c ft_panel.c ft_textures.c ft_display.c ft_ray_casting.c ft_details_display.c\
ft_ray_casting_hor.c ft_ray_casting_vert.c ft_move.c parse.c parse_args_utils.c parse_args_utils2.c parse_map.c\
ft_create_tiles_utils.c ft_move_left_right.c ft_move_up_down.c
SRCM = $(addprefix src/, $(SRC))
OBJ = $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o))
SRCB_TMP = main.c get_next_line.c get_next_line_utils.c \
			ft_read_map.c ft_create_tiles.c ft_check.c
SRCB = $(addprefix bonus/, $(SRCB_TMP))
OBJB = $(addprefix $(DIR_OBJ)/, $(SRCB_TMP:.c=.o))
#FLAGS = -g -Iminilibx-linux -Ilibft
#FLAGS =  -g -Iminilibx_opengl -Ilibft
FLAGS = -Wall -Wextra -Werror -g -Iminilibx_opengl -Ilibft
#LINKS = -I/usr/include -Ilibft -Iminilibx_opengl -L./minilibx_opengl -lmlx -L./libft -lft -framework OpenGL -framework AppKit
#LINKS = -I/usr/include -L/usr/lib -L./minilibx_opengl -lmlx -framework OpenGL -framework AppKit -Iminilibx_opengl -L./libft -lft -lX11
LINKS = -I/usr/include -L./minilibx_opengl -lmlx -framework OpenGL -framework AppKit -Iminilibx_opengl -L./libft -lft
#LINKS = -I/usr/include -Iminilibx_linux -L./minilibx-linux -lmlx_Linux -L/usr/lib -L./libft -lft -lXext -lX11 -lm -lz
#LINKS = -I/usr/include -Iminilibx_linux -L./minilibx-linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
all: $(NAME)

$(NAME): ./libft/libft.a $(OBJ)
	gcc $(FLAGS) $(OBJ) $(LINKS) -o $(NAME)

$(DIR_OBJ)/%.o : ./src/%.c ./src/cub3.h
	mkdir -p $(DIR_OBJ)
	gcc -g3 $(FLAGS) -c $< -o $@

./libft/libft.a : libft;

libft :
	$(MAKE) bonus -C ./libft

./minilibx_opengl/libmlx.a : minilibx;

minilibx :
	$(MAKE) -C ./minilibx_opengl

clean:
	rm -rf $(DIR_OBJ)
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./minilibx_opengl

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C ./libft

re : fclean all

.PHONY : fclean all re clean libft minilibx
