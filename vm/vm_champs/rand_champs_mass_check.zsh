CHFOLDER="champs/championships/"
champs=($(ls -R $CHFOLDER | grep -E "(/|\.s)" | sed -e ':a' -e 'N' -e '$!ba' -e 's|:\n|/|g' -e "s/\.s//g"))
cn=${#champs[@]}
NEEDED_CHAMP_NUM=4

for (( i=0; i<$NEEDED_CHAMP_NUM; i++))
do
	rand=$RANDOM
	./asm "${champs[$((rand%cn))]}.s"
	rchamps[$i]="${champs[$((rand%cn))]}.cor";
done

./mass_checker.zsh ${rchamps[@]}
