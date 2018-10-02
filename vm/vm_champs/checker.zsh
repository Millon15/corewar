#!/bin/bash

# That file needs to be launched in corewar/vm/vm_champs folder

i=$RANDOM
PREFIX="/tmp/"
ORIG_LOG=${PREFIX}log_${i}
OURS_LOG=${PREFIX}log__${i}
DIFF=${PREFIX}diff_${i}

make -C ..
echo -n > $ORIG_LOG; echo -n > $OURS_LOG; echo -n > $DIFF
rm -f log1 log diff
ln -s $ORIG_LOG log1
ln -s $OURS_LOG log
ln -s $DIFF diff
./corewar $* > $ORIG_LOG &
../corewar $* > $OURS_LOG
diff $ORIG_LOG $OURS_LOG > $DIFF; wc -l < $DIFF
if [[ $(cat $DIFF) ]];
then
	less $DIFF;
else
	rm -f $ORIG_LOG $OURS_LOG $DIFF
fi
