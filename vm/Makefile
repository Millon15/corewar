# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/13 19:52:44 by vbrazas           #+#    #+#              #
#    Updated: 2018/09/02 21:44:38 by vbrazas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := corewar

SRC_PATH := src/
OP_PATH := $(SRC_PATH)operations/
V_PATH := $(SRC_PATH)visualizer/
INC_PATH := includes/
LIB_PATH := ../ft_printf/
OBJ_PATH := .obj/

CC := clang
CFLAGS := -g #-Wall -Werror -Wextra
IFLAGS := -I ../../$(INC_PATH) -I $(INC_PATH) -I $(LIB_PATH)
LFLAGS := -lncurses

HFILES :=		vm
OPERATIONS :=	add aff and ld ldi lfork live lld lldi op_fork or st sti sub xor zjmp
FILES :=		vm errors utils args_parsing fill_the_map carriage carriage_utils main_cycle_funcs
VISUALIZER :=	v_main v_init v_print
LIB :=			$(LIB_PATH)libftprintf.a

HDRS := $(addprefix $(INC_PATH), $(addsuffix .h, $(HFILES)))
SRCS := $(addprefix $(OP_PATH), $(addsuffix .c, $(OPERATIONS)))
SRCS += $(addprefix $(SRC_PATH), $(addsuffix .c, $(FILES)))
SRCS += $(addprefix $(V_PATH), $(addsuffix .c, $(VISUALIZER)))
OBJS := $(addprefix $(OBJ_PATH), $(SRCS:%.c=%.o))


all: $(NAME)

$(NAME): $(LIB) $(OBJ_PATH) $(OBJS)
	$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) $(OBJS) $(LIB) -o $(NAME)
$(LIB): 
	make -C $(LIB_PATH)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)$(OP_PATH)
	mkdir -p $(OBJ_PATH)$(V_PATH)
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