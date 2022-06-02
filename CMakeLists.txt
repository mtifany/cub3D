cmake_minimum_required(VERSION 3.20)
project(cub3d C)

set(CMAKE_C_STANDARD 99)
add_executable(cub3d src/main.c src/ft_read_map.c src/ft_create_tiles.c src/get_next_line_utils.c src/get_next_line.c src/ft_check.c
        src/ft_free.c src/ft_free1.c src/ft_panel.c src/ft_textures.c src/ft_display.c src/ft_ray_casting.c
        src/ft_ray_casting_hor.c src/ft_move.c src/ft_details_display.c src/parse.c src/parse_args_utils2.c src/parse_args_utils.c src/parse_map.c)

target_link_libraries(cub3d "-framework OpenGL -framework AppKit")
target_link_libraries(cub3d /Users/mtifany/CLionProjects/cub3d/minilibx_opengl/libmlx.a)
target_link_libraries(cub3d /Users/mtifany/CLionProjects/cub3d/libft/libft.a)