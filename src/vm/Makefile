# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/02 18:58:59 by vbrazas           #+#    #+#              #
#    Updated: 2018/08/05 21:16:50 by vbrazas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

SRC_PATH = src/
LIB_PATH = ../../ft_printf/
OBJ_PATH = .obj/

CC = clang
CFLAGS = #-Wall -Werror -Wextra

INC_PATH = includes/
IFLAGS = -I ../../$(INC_PATH) -I $(INC_PATH) -I $(LIB_PATH)

HFILES = vm
FILES = vm errors utils args_parsing fill_the_map carriage
LIB = $(LIB_PATH)libftprintf.a

HDRS = $(addprefix $(INC_PATH), $(addsuffix .h, $(HFILES)))
SRCS = $(addprefix $(SRC_PATH), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJ_PATH), $(SRCS:%.c=%.o))


all: $(NAME)

$(NAME): $(LIB) $(OBJ_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LIB) -o $(NAME) 

$(LIB): 
	make -C $(LIB_PATH)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)$(SRC_PATH)
$(OBJ_PATH)%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

clean: mclean
	make clean -C $(LIB_PATH)
fclean: mfclean
	make fclean -C $(LIB_PATH)
re: fclean all

mclean:
	rm -f $(OBJS) $(DEPS)
mfclean:
	rm -f $(NAME)
	rm -rf $(OBJ_PATH)
mre: mfclean all

.PHONY: all clean fclean re mclean mfclean mre
