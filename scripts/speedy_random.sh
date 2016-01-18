for i in map-read-only/random/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./gppc-2015-submission/Speedy/Speedy -full map-read-only/random/${i##*/} scenarios-read-only/random/${i##*/}.scen > speedy/Speedy_${i##*/}_result.txt
fi
done
