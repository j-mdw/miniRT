TEST_FILES = parsing/parse_main.c parsing/parse_params.c parsing/parse_utils.c parsing/parse_errors_free.c \
	     parsing/gnl/get_next_line.c parsing/gnl/get_next_line_utils.c

all: 
	gcc -Wall -Werror -Wextra mymlxtst.c -Lmlx_linux minilibx-linux/libmlx.a -L/usr/lib -lXext -lX11 -lm

test:
	gcc -Wall -Werror -Wextra -I libft/ -I parsing/ $(TEST_FILES) libft/libft.a

clean:
	rm a.out
