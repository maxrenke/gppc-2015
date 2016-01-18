rm results/mazes_results.txt
for i in map-read-only/mazes/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./result.py mazes ${i##*/} >> results/mazes_results.txt
fi
done
