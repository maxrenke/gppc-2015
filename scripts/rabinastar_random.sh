for i in map-read-only/random/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./rabinastar.out -full map-read-only/random/${i##*/} scenarios-read-only/random/${i##*/}.scen > rabinastar/rabinastar_random_${i##*/}_result.txt
fi
done
