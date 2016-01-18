for i in map-read-only/dao/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./gppc-2015-submission/Speedy/Speedy -full map-read-only/dao/${i##*/} scenarios-read-only/dao/${i##*/}.scen > speedy/Speedy_dao_${i##*/}_result.txt
fi
done
