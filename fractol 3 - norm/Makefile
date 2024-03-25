# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarzouk <amarzouk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/22 14:36:55 by amarzouk          #+#    #+#              #
#    Updated: 2024/03/25 10:47:59 by amarzouk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, main.c events.c init.c math.c ft_printf.c render.c helper.c printf_helper.c render2.c)
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L minilibx -lmlx -framework OpenGL -framework AppKit
MINILIBX_DIR = minilibx

all: minilibx $(NAME)
minilibx:
	@echo "Building minilibx..."
	@make -C $(MINILIBX_DIR)

$(NAME): $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)


fclean: clean
	rm -f $(NAME)
	make -C $(MINILIBX_DIR) clean

re: fclean all

.PHONY: all clean fclean re minilibx