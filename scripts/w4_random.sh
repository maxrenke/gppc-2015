for i in map-read-only/random/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./gppc-2015-submission/weightedAStar_4/wAStar_4 -full map-read-only/random/${i##*/} scenarios-read-only/random/${i##*/}.scen > w4/w4_${i##*/}_result.txt
fi
done
