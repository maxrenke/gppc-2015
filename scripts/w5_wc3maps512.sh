for i in map-read-only/wc3maps512/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./gppc-2015-submission/weightedAStar_5/wAStar_5 -full map-read-only/wc3maps512/${i##*/} scenarios-read-only/wc3maps512/${i##*/}.scen > w5/w5_${i##*/}_result.txt
fi
done
