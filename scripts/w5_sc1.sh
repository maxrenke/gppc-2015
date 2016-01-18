for i in map-read-only/local/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./gppc-2015-submission/weightedAStar_5/wAStar_5 -full map-read-only/local/${i##*/} scenarios-read-only/local/${i##*/}.scen > w5/w5_local_${i##*/}_result.txt
fi
done
