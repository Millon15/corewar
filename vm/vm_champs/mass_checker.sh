#!/bin/bash

# That file needs to be launched in corewar/vm/vm_champs folder

j=1
fact=1
for i in $*;
do
	let fact*=$j
	let j++
done
let fact*=2
# let fact=6
echo "Start testing $fact combinations of this bots: $*"

ARGS=($*)
ARG_NUM=4
PREFIX="/tmp/"
TO_DO="to_do.sh"
ERR_D="/tmp/errors/"
mkdir -p $ERR_D
ERRORS=$ERR_D"err_list"
ERRNUM=$(ls -1r $ERR_D | grep diff_ | head -1)
ERRNUM=$(($ERRNUM+0))

make -C ..
rm -f ${PREFIX}diff_* ${PREFIX}log_* $TO_DO
echo -n > $TO_DO

for i in `seq 1 $fact`;
do
	let j=$RANDOM%$ARG_NUM

	let i=$ARG_NUM-1
	VMAV=""
	for l in `seq 0 $i`;
	do
		let k=($j+$l)%$ARG_NUM
		VMAV="$VMAV ${ARGS[$k]}"
	done

	let i=$RANDOM
	ORIG_LOG=${PREFIX}log_$i
	OURS_LOG=${PREFIX}log__$i
	DIFF=${PREFIX}diff_$i
	while [[ $(grep -E "$ORIG_LOG|$OURS_LOG|$DIFF" $TO_DO) ]];
	do
		echo BAD RANDOM $i
		let i=$RANDOM
		ORIG_LOG=${PREFIX}log_$i
		OURS_LOG=${PREFIX}log__$i
		DIFF=${PREFIX}diff_$i
	done
	echo -n > $DIFF; echo -n > $ORIG_LOG; echo -n > $OURS_LOG
	./corewar -d 16000 $VMAV > $ORIG_LOG &
	../corewar -d 16000 $VMAV > $OURS_LOG &
	echo "diff $ORIG_LOG $OURS_LOG > $DIFF" >> $TO_DO
	echo "# ERRNUM=$ERRNUM # $VMAV" >> $TO_DO
	sleep 1
done

while [[ $(pgrep corewar) ]];
do
	echo -n "Waiting... for "
	echo -n $(pgrep corewar | wc -l)
	echo " proccesses"
	sleep 10
done
chmod 744 $TO_DO
./$TO_DO

let j=ERRNUM
for i in $(ls -1 ${PREFIX} | grep diff_)
do
	is_err=$(wc -l < ${PREFIX}$i)
	if [[ $(($is_err+0)) != 0 ]];
	then
		if [[ $ERRNUM == $j ]];
		then
			echo >> $ERRORS
		fi
		rand=$(echo $i | cut -d'_' -f 2)
		cp ${PREFIX}diff_$rand ${ERR_D}diff_${j}
		cp ${PREFIX}log_$rand ${ERR_D}log_${j}
		cp ${PREFIX}log__$rand ${ERR_D}log__${j}
		grep -A 1 $i $TO_DO >> $ERRORS
		let j++
	fi
done
echo "Number of wrong player combinations: $(($j-$ERRNUM))"
sleep 5
if [[ $ERRNUM < $j ]];
then
	less $ERRORS
else
	rm -f ${PREFIX}diff_* ${PREFIX}log_* $TO_DO
fi
