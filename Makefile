# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmaydew <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 19:10:11 by jmaydew           #+#    #+#              #
#    Updated: 2020/11/17 19:34:50 by jmaydew          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TEST_FILES = main.c my_mlx_pixel_put.c hooks.c movements.c save_minirt.c \
			initializer.c \
			parsing/parse_params_1.c parsing/parse_params_2.c \
			parsing/parse_params_3.c parsing/parse_utils_1.c \
			parsing/parse_errors_free.c parsing/gnl/get_next_line.c \
			parsing/gnl/get_next_line_utils.c parsing/parse_utils_2.c \
			parsing/parse_utils_3.c \
			raytracing/shoot_ray.c raytracing/lights.c \
			raytracing/intersections_1.c raytracing/intersections_2.c \
			raytracing/vectors_utils_1.c raytracing/vectors_utils_2.c \
			raytracing/set_normals.c raytracing/raytrace_utils.c
	
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3

all: 
	gcc $(CFLAGS) -I libft/ -I includes/ -I parsing/gnl/ $(TEST_FILES) libft/libft.a -Lmlx_linux libmlx.a -L/usr/lib -lXext -lX11 -lm

#test: $(TEST_FILES)
#	gcc -Wall -Werror -Wextra -I libft/ -I parsing/ $(TEST_FILES) libft/libft.a -o minirt_parse -lm

clean:
	rm minirt_parse

fclean: clean

re: fclean all

.PHONY: all bonus clean fclean re
