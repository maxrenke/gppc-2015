for i in map-read-only/local/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./a.out -full map-read-only/local/${i##*/} scenarios-read-only/local/${i##*/}.scen > rabinastarbucket/rabinastarbucket_local_${i##*/}_result.txt
fi
done
