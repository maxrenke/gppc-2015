rm results/sc1_results.txt
for i in map-read-only/sc1/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./result.py sc1 ${i##*/} >> results/sc1_results.txt
fi
done
