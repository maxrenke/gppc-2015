rm results/random_results.txt
for i in map-read-only/random/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./result.py random ${i##*/} >> results/random_results.txt
fi
done
