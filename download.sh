#!/bin/bash

ADDR="http://yann.lecun.com/exdb/mnist"
FILES=(train-images-idx3-ubyte.gz train-labels-idx1-ubyte.gz t10k-images-idx3-ubyte.gz t10k-labels-idx1-ubyte.gz)
VAL=($(ls data 2> /dev/null));


contains() {
	local item="$1"
	if [[ ${VAL[@]} =~ (^|[[:space:]])$item($|[[:space:]]) ]]; then
		return 0;
	else
		return 1;
	fi
}

prog() {
    local w=25 p=$1 f=$2;  shift
    printf -v dots "%*s" "$(( $p*$w/100 ))" " "; dots=${dots// /\#};
    printf "\r\e[K ⚡ Téléchargement [%-*s] %3d %% %s" "$w" "$dots" "$p" "$*";
}

for i in ${!FILES[@]}; do
	f=${FILES[$i]}
	f_name=`echo $f|sed "s/.gz//g"`;
	prog $(( ($i+1)*100/${#FILES[@]} )) "→ $f_name "
	if ! [ -f data/$f_name ]; then
		curl -s --create-dirs $ADDR/$f -o data/$f;
		gunzip data/$f;
	fi
done
printf "\n"
