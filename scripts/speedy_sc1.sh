for i in map-read-only/local/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./gppc-2015-submission/Speedy/Speedy -full map-read-only/local/${i##*/} scenarios-read-only/local/${i##*/}.scen > speedy/Speedy_local_${i##*/}_result.txt
fi
done
