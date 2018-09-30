#!/bin/bash

# That file needs to be launched in corewar/vm/vm_champs folder

i=$RANDOM
PREFIX="/tmp/"
ORIG_LOG=${PREFIX}log_${i}
OURS_LOG=${PREFIX}log__${i}
DIFF=${PREFIX}diff_${i}

make -C ..
echo -n > $ORIG_LOG; echo -n > $OURS_LOG; echo -n > $DIFF
./corewar $* > $ORIG_LOG &
../corewar $* > $OURS_LOG
diff $ORIG_LOG $OURS_LOG > $DIFF; wc -l < $DIFF;
if [[ $(head $DIFF) ]];
then
	less diff;
else
	rm -f $ORIG_LOG $OURS_LOG $DIFF
fi
