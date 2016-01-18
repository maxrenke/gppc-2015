for i in map-read-only/local/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./gppc-2015-submission/weightedAStar_4/wAStar_4 -full map-read-only/local/${i##*/} scenarios-read-only/local/${i##*/}.scen > w4/w4_local_${i##*/}_result.txt
fi
done
