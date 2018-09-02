# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/13 19:52:44 by vbrazas           #+#    #+#              #
#    Updated: 2018/09/02 22:08:26 by vbrazas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := asm

SRC_PATH := src/
INC_PATH := includes/
LIB_PATH := $(INC_PATH)libft/
OBJ_PATH := .obj/

CC := clang
CFLAGS := -Wall -Werror -Wextra
IFLAGS := -I $(INC_PATH)

HFILES :=		op asm libft/libft
FILES :=		args args2 args3 botsize cmd comment detect global_operations label libft_d main name set_value write_in_file
LIB :=			$(LIB_PATH)libft.a

HDRS := $(addprefix $(INC_PATH), $(addsuffix .h, $(HFILES)))
SRCS := $(addprefix $(SRC_PATH), $(addsuffix .c, $(FILES)))
OBJS := $(addprefix $(OBJ_PATH), $(SRCS:%.c=%.o))


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
