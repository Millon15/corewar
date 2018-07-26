# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/28 19:24:02 by vbrazas           #+#    #+#              #
#    Updated: 2018/07/26 14:47:46 by vbrazas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NVM = corewar
NASM = asm

SRC_PATH = src/
VM_PATH = $(SRC_PATH)/vm
ASM_PATH = $(SRC_PATH)/asm
LIB_PATH = ft_printf/
INC_PATH = includes/
OBJ_PATH = obj/

C = clang
WFLAGS = #-Wall -Werror -Wextra
IFLAGS = -I $(INC_PATH) -I $(LIB_PATH)

LIB = $(LIB_PATH)libftprintf.a
COMMON_NAMES = common
VM_NAMES = main
ASM_NAMES = 

COMMON = $(addprefix $(SRC_PATH), $(addsuffix .c, $(COMMON_NAMES)))
VM = $(addprefix $(VM_PATH), $(addsuffix .c, $(VM_NAMES)))
ASM = $(addprefix $(ASM_PATH), $(addsuffix .c, $(ASM_NAMES)))
OBJ_COMM = $(addprefix $(OBJ_PATH), $(COMMON:%.c=%.o))
OBJ_VM = $(addprefix $(OBJ_PATH), $(VM:%.c=%.o))
OBJ_ASM = $(addprefix $(OBJ_PATH), $(ASM:%.c=%.o))


all: $(COMMON) $(VM) $(ASM)

$(COMMON): $(LIB) $(OBJ_COMMON)

$(NVM): $(COMMON) $(OBJ_VM)
	$(C) $(WFLAGS) $(IFLAGS) $(LIB) $(OBJ_VM) -o $(NVM)

$(NASM): $(COMMON) $(OBJ_ASM)
	$(C) $(WFLAGS) $(IFLAGS) $(LIB) $(OBJ_ASM) -o $(NASM)


$(LIB):
	make -C $(LIB_PATH)

$(OBJ): | $(OBJ_PATH)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)$(VM_PATH)
	mkdir -p $(OBJ_PATH)$(ASM_PATH)

$(OBJ_PATH)%.o: %.c
	$(C) $(WFLAGS) $(IFLAGS) -c $< -o $@

clean:
	make clean -C $(LIB_PATH)
	rm -f $(OBJ)

fclean:
	make fclean -C $(LIB_PATH)
	rm -f $(NAME)
	rm -rf $(OBJ_PATH)

re: fclean all

mclean:
	rm -f $(OBJ)

mfclean:
	rm -f $(NAME)
	rm -rf $(OBJ_PATH)

mre: mfclean all

.PHONY: all clean fclean re
