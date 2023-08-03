# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arepsa <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/01 10:56:34 by arepsa            #+#    #+#              #
#    Updated: 2023/08/03 09:21:48 by arepsa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf
SRCS_DIR	=	srcs
OBJS_DIR	=	objs
INCLUDES	=	includes
LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft
LIBMLX		=	./mlx/libmlx.a
MLX_DIR		=	./mlx

SRCS		=	1_main.c \
				2_errors.c \
				3_read_map.c \
				4_draw_map.c \
				5_draw_line.c \
				6_transform_map.c \
				7_draw_utils.c	

CC			= cc
LIBFLAGS	= ar -rcs
RM			= rm -rf

CFLAGS		= -Wall -Wextra -Werror -g 
MLXFLAGS	= -lmlx -lXext -lX11 -lm -lbsd
MK_FLAG		= --no-print-directory


OBJS		= $(SRCS:%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	$(CC) $(CFLAGS) $(OBJS) -L$(MLX_DIR) $(MLXFLAGS) $(LIBFT) -o $(NAME)
	echo "Done compiling fdf!"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	echo "Creating $(NAME) .o files..."
	mkdir -p $(@D)
	$(CC) -I $(INCLUDES) $(CFLAGS) -c $< -o $@

$(LIBFT):
	echo "Making libft..."
	$(MAKE) $(MK_FLAG) -C $(LIBFT_DIR)

$(LIBMLX):
	echo "Making MiniLibX..."
	$(MAKE) $(MK_FLAG) -sC $(MLX_DIR)

clean:
	$(RM) $(OBJS_DIR)
	echo "Deleted $(NAME) $(OBJS_DIR)"
	$(MAKE) $(MK_FLAG) clean -C $(LIBFT_DIR)
	$(MAKE) $(MK_FLAG) clean -C $(MLX_DIR)

fclean: clean
	$(RM) $(NAME) $(LIBFT)
	echo "Deleted $(NAME) and $(LIBFT)"
	
re: fclean all

.PHONY: all clean fclean re
.SILENT:
