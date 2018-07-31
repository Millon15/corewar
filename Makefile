# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vbrazas <vbrazas@student.unit.ua>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/28 19:24:02 by vbrazas           #+#    #+#              #
#    Updated: 2018/07/31 14:45:19 by vbrazas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM = asm
VM = corewar

SRC_PATH = src/
ASM_PATH = $(SRC_PATH)asm/
VM_PATH = $(SRC_PATH)vm/


all: $(ASM) $(VM)

$(ASM):
	make -C $(ASM_PATH)
	mv $(ASM_PATH)$(ASM) .

$(VM):
	make -C $(VM_PATH)
	mv $(VM_PATH)$(VM) .

clean:
	make clean -C $(ASM_PATH)
	make clean -C $(VM_PATH)

fclean:
	make fclean -C $(ASM_PATH)
	make fclean -C $(VM_PATH)

re: fclean all

mclean:
	make mclean -C $(ASM_PATH)
	make mclean -C $(VM_PATH)

mfclean:
	make mfclean -C $(ASM_PATH)
	make mfclean -C $(VM_PATH)
	rm -f $(ASM) $(VM)

mre: mfclean all

.PHONY: all clean fclean re mclean mfclean mre
