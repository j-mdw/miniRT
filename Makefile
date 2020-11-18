# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 19:10:11 by jmaydew           #+#    #+#              #
#    Updated: 2020/11/18 12:58:32 by jmaydew          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minirt

C_FILES =	main.c \
			actions/my_mlx_pixel_put.c actions/hooks.c \
			actions/movements.c actions/save_minirt.c \
			actions/initializer.c \
			parsing/parse_params_1.c parsing/parse_params_2.c \
			parsing/parse_params_3.c parsing/parse_utils_1.c \
			parsing/parse_errors_free.c parsing/gnl/get_next_line.c \
			parsing/gnl/get_next_line_utils.c parsing/parse_utils_2.c \
			parsing/parse_utils_3.c \
			raytracing/shoot_ray.c raytracing/lights.c \
			raytracing/intersections_1.c raytracing/intersections_2.c \
			raytracing/vectors_utils_1.c raytracing/vectors_utils_2.c \
			raytracing/set_normals.c raytracing/raytrace_utils.c
LIBFT = libft/libft.a
O_FILES = $(REG_SRC_FILES:c=o)
INCLUDES =	includes/minirt.h minilibx-linux/mlx.h libft/libft.h \
			parsing/gnl/get_next_line.h
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3

all: $(NAME)

$(NAME): $(C_FILES) $(LIBFT) $(INCLUDES)
	gcc $(CFLAGS) -I libft/ -I includes/ -I parsing/gnl/ -I minilibx-linux/ $(C_FILES) \
	libft/libft.a -Lmlx_linux minilibx-linux/libmlx.a -L/usr/lib -lXext -lX11 -lm -o $(NAME)

$(LIBFT): libft/libft.h
	$(MAKE) -C libft

clean:
	rm -f libft/*.o

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all

.PHONY: all bonus clean fclean re
