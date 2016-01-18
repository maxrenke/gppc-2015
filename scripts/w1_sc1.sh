for i in map-read-only/local/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./gppc-2015-submission/weightedAStar_1_1/wAStar_1_1 -full map-read-only/local/${i##*/} scenarios-read-only/local/${i##*/}.scen > w1/w1_local_${i##*/}_result.txt
fi
done
