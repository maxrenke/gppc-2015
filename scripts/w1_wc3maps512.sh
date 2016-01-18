for i in map-read-only/wc3maps512/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./gppc-2015-submission/weightedAStar_1_1/wAStar_1_1 -full map-read-only/wc3maps512/${i##*/} scenarios-read-only/wc3maps512/${i##*/}.scen > w1/w1_${i##*/}_result.txt
fi
done
