NAME		=	fdf.a
SRCS_DIR	=	srcs
OBJS_DIR	=	objs
INCLUDES	=	includes
LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft

SRCS		=	main.c

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
MLXFLAGS	= -lmlx -lXext -lX11 -lm -lbsd
LIBFLAGS	= ar -rcs
RM			= rm -rf

OBJS		= $(SRCS:%.c=$(OBJS_DIR)/%.o)

all:    $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(LIBFLAGS) $(NAME) $(OBJS)
	$(CC) $(NAME) -L./mlx/. $(LIBFT) $(CFLAGS) $(MLXFLAGS) -o fdf
	@echo "Done compiling!"

$(OBJS): $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -I. -O3 $(CFLAGS) -I.. -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re


