# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/02 18:58:59 by vbrazas           #+#    #+#              #
#    Updated: 2018/08/02 19:43:12 by vbrazas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

SRC_PATH = src/
LIB_PATH = ../../ft_printf/
OBJ_PATH = .obj/
# OBJ_PATH = .dep/

CC = clang
CFLAGS = -Wall -Werror -Wextra

INC_PATH = includes/
IFLAGS = -I ../../$(INC_PATH) -I $(INC_PATH) -I $(LIB_PATH)

LIB = $(LIB_PATH)libftprintf.a
FILES = main fill_the_map

SRCS = $(addprefix $(SRC_PATH), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJ_PATH), $(SRCS:%.c=%.o))
# DEPS = $(SRCS:.c=.d)


all: $(NAME)

$(NAME): $(LIB) $(OBJ_PATH) $(DEP_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(OBJS) $(LIB) -o $(NAME) 

$(LIB): 
	make -C $(LIB_PATH)

# -include $(DEPS)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)$(SRC_PATH)
# $(DEP_PATH):
#	mkdir -p $(DEP_PATH)$(SRC_PATH)
$(OBJ_PATH)%.o: %.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
# 	$(CC) $(CFLAGS) $(IFLAGS) -MM $< > $*.d

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
