for i in map-read-only/dao/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./gppc-2015-submission/weightedAStar_1_1/wAStar_1_1 -full map-read-only/dao/${i##*/} scenarios-read-only/dao/${i##*/}.scen > w5/w5_dao_${i##*/}_result.txt
fi
done
