#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndidenko <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/31 16:25:55 by ndidenko          #+#    #+#              #
#    Updated: 2017/10/31 16:28:36 by ndidenko         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a

SRCS =	ft_memcpy.c \
		ft_striteri.c \
		ft_memdel.c \
		ft_strjoin.c \
		ft_atoi.c \
		ft_memmove.c \
		ft_strlcat.c \
		ft_bzero.c \
		ft_memset.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_isalnum.c \
		ft_putchar.c \
		ft_strmapi.c \
		ft_isalpha.c \
		ft_putchar_fd.c \
		ft_strncat.c \
		ft_isascii.c \
		ft_putendl.c \
		ft_strncmp.c \
		ft_isdigit.c \
		ft_putendl_fd.c \
		ft_strncpy.c \
		ft_isprint.c \
		ft_putnbr.c \
		ft_strnequ.c \
		ft_itoa.c \
		ft_putnbr_fd.c \
		ft_strnew.c \
		ft_lstadd.c \
		ft_putstr.c \
		ft_strnstr.c \
		ft_lstdel.c \
		ft_putstr_fd.c \
		ft_strrchr.c \
		ft_lstdelone.c \
		ft_strcat.c \
		ft_lstiter.c \
		ft_strchr.c \
		ft_strsplit.c \
		ft_lstmap.c \
		ft_strclr.c \
		ft_strstr.c \
		ft_lstnew.c \
		ft_strcmp.c \
		ft_strsub.c \
		ft_strcpy.c \
		ft_memalloc.c \
		ft_strdel.c \
		ft_strtrim.c \
		ft_memccpy.c \
		ft_strdup.c \
		ft_tolower.c \
		ft_memchr.c \
		ft_strequ.c \
		ft_toupper.c \
		ft_memcmp.c \
		ft_striter.c \
		ft_isupper.c \
		ft_islower.c \
		ft_lstsize.c \
		ft_is_space.c \
		get_next_line.c \
		ft_main.c \
		ft_print_conv.c \
		parsing.c \
		processing_s.c \
		processing_c.c \
		processing_invalid.c \
		left_right.c \
		processing_u.c \
		processing_u_1.c \
		processing_p.c \
		processing_d.c \
		processing_d_1.c \
		processing_o.c \
		processing_o_1.c \
		processing_x.c \
		processing_x_1.c \
		processing_x_2.c \
		processing_x_3.c \
		processing_unicode.c \
		processing_pct.c \
		check.c \
		ft_2to10.c \
		ft_itoa_max.c \

FLAGS = -Wall -Wextra -Werror

OBJ = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

%.o: %.c
	@gcc $(FLAGS) -c $< -o $@
	
clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all
