rm results/dao_results.txt
for i in map-read-only/dao/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./result.py dao ${i##*/} >> results/dao_results.txt
fi
done
