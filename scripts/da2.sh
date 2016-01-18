rm results/da2_results.txt
for i in map-read-only/da2/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./result.py da2 ${i##*/} >> results/da2_results.txt
fi
done
