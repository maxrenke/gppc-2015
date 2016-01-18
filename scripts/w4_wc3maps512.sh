for i in map-read-only/wc3maps512/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./gppc-2015-submission/weightedAStar_4/wAStar_4 -full map-read-only/wc3maps512/${i##*/} scenarios-read-only/wc3maps512/${i##*/}.scen > w4/w4_${i##*/}_result.txt
fi
done
