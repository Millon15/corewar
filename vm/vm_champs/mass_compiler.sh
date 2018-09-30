#!/bin/bash

# That file needs to be launched in corewar/vm/vm_champs folder

TO_COMP_D="champs/"

for i in $(ls -1 $TO_COMP_D | grep "\.s");
do
	./asm $TO_COMP_D$i &> /dev/null;
	COR="$TO_COMP_D$(echo $i | cut -d'.' -f1).cor"
	if [[ $(./corewar -d 10 $COR 1> /dev/null) ]];
	then
		rm -f $COR
	fi
done
