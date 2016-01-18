for i in map-read-only/random/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./gppc-2015-submission/weightedAStar_5/wAStar_5 -full map-read-only/random/${i##*/} scenarios-read-only/random/${i##*/}.scen > w5/w5_${i##*/}_result.txt
fi
done
