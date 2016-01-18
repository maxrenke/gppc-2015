for i in map-read-only/random/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./gppc-2015-submission/weightedAStar_1_1/wAStar_1_1 -full map-read-only/random/${i##*/} scenarios-read-only/random/${i##*/}.scen > w1/w1_${i##*/}_result.txt
fi
done
