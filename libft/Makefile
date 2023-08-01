# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arepsa <arepsa@student.42porto.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/19 11:38:57 by arepsa            #+#    #+#              #
#    Updated: 2023/07/13 17:40:21 by arepsa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= libft.a
OBJS_DIR	:=	objs
		
SRCS =	ft_atoi.c		ft_bzero.c		ft_calloc.c\
		ft_isalnum.c	ft_isalpha.c	ft_isascii.c\
		ft_isdigit.c	ft_isprint.c	ft_itoa.c\
		ft_memchr.c		ft_memcmp.c		ft_memcpy.c\
		ft_memmove.c	ft_memset.c		ft_putchar_fd.c\
		ft_putendl_fd.c	ft_putnbr_fd.c	ft_putstr_fd.c\
		ft_split.c		ft_strchr.c		ft_strdup.c\
		ft_striteri.c	ft_strjoin.c	ft_strlcat.c\
		ft_strlcpy.c	ft_strlen.c		ft_strmapi.c\
		ft_strncmp.c	ft_strnstr.c	ft_strrchr.c\
		ft_strtrim.c	ft_substr.c		ft_tolower.c\
		ft_toupper.c	ft_lstnew.c	ft_lstadd_front.c\
		ft_lstsize.c	ft_lstlast.c	ft_lstadd_back.c\
		ft_lstdelone.c	ft_lstclear.c	ft_lstmap.c\
		ft_lstiter.c	ft_count_words.c\
		ft_atoi_hex.c\
		ft_printf/ft_printf.c	ft_printf/ft_printf_ptr.c\
		ft_printf/ft_printf_utils.c\
		get_next_line/get_next_line.c	get_next_line/get_next_line_utils.c

CC	:= cc
CFLAGS	:= -Wall -Wextra -Werror
CPPFLAGS = -I. #include header files that are in the current directory
LIBFLAGS	:= ar -rcs #create and index library
RM	:= rm -rf
SRCS_O	:= $(SRCS:%.c=$(OBJS_DIR)/%.o) #substitute .c with .o

#create and index library (ar - archive, -r insert files by replacement, -c create the archve, -s index the files

#create .o files; also default compilation
# $< first prerequisite aka .c; $@ output/targer file aka .o
$(OBJS_DIR)/%.o : %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

#default target - create libft.a
all: $(NAME)

#Mandatory part
$(NAME): $(SRCS_O)
	$(LIBFLAGS) $(NAME) $(SRCS_O)
	echo "Done compiling libft!"

#remove .o files
clean:
	$(RM) $(OBJS_DIR)
	echo "Deleted libft $(OBJS_DIR)"

#remove static library
fclean: clean
	$(RM) $(NAME)
	echo "Deleted $(NAME)"

#reset environment - remove everything and recompile
re: fclean all

#targets declared as .PHONY will force the command even if there is a subdirectory or file with it's name
.PHONY: all clean fclean re
.SILENT: