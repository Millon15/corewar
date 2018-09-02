# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/28 19:24:02 by vbrazas           #+#    #+#              #
#    Updated: 2018/09/02 18:14:19 by akupriia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM := asm
VM := corewar

SRC_PATH := src/
ASM_PATH := $(SRC_PATH)asm/
VM_PATH := $(SRC_PATH)vm/


all:
	# make -C $(ASM_PATH)
	# cp $(ASM_PATH)$(ASM) .
	make -C $(VM_PATH)
	cp $(VM_PATH)$(VM) .

mre:
	make mre -C $(ASM_PATH)
	make mre -C $(VM_PATH)
	cp $(VM_PATH)$(VM) .
clean:
	make clean -C $(ASM_PATH)
	make clean -C $(VM_PATH)
fclean:
	make fclean -C $(ASM_PATH)
	make fclean -C $(VM_PATH)
	rm -f $(ASM) $(VM)
re: fclean all

.PHONY: all clean fclean re mre
