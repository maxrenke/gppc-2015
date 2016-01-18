for i in map-read-only/wc3maps512/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./gppc-2015-submission/Speedy/Speedy -full map-read-only/wc3maps512/${i##*/} scenarios-read-only/wc3maps512/${i##*/}.scen > speedy/Speedy_${i##*/}_result.txt
fi
done
