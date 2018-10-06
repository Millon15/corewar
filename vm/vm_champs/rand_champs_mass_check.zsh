CHFOLDER="."
champs=$(ls -R $CHFOLDER | grep -E "(/|.*\.s$)" | sed -e ':a' -e 'N' -e '$!ba' -e "s/\.s//g")

j=0;
for champ in $champs; do
	if [[ $(echo $champ | grep ":$") ]]; then
		path=$(echo $champ | sed -e "s|:|/|g")
	else
		# ./asm "${path}$champ.s"
		found[$j]="${path}$champ.cor"
		let j++
	fi
done

cn=${#found[@]}
NEEDED_CHAMP_NUM=4

for (( i=0; i<$NEEDED_CHAMP_NUM; i++)); do
	rchamps[$i]="${found[$(($RANDOM%cn))]}";
done

./mass_checker.zsh ${rchamps[@]}
