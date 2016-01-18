rm results/wc3maps512_results.txt
for i in map-read-only/wc3maps512/*; 
do if [[ $i =~ \.map$ ]]
	then
		echo ${i##*/}
		./result.py wc3maps512 ${i##*/} >> results/wc3maps512_results.txt
fi
done
