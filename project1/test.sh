test_set=(./data/ch4.h5 ./data/h2o.h5 ./data/c2h2.h5 ./data/hcn.h5 ./data/h3coh.h5 ./data/co2.h5)
hf_ref=(-40.19867 -76.02679 -76.82577 -92.88295 -115.04842 -187.65071)
mp2_ref=(-40.362681 -76.230759 -77.085873 -93.172222 -115.391507 -188.139385)

if [ ! -d tests ]; then
	mkdir tests
fi


for (( i=0;i<${#test_set[@]};i++))
do
	file=${test_set[i]}
	if [ ! -e $file ]; then
		echo "$file does not exist"
		continue
	fi

	dest_dir=${file/data/tests}
	dest_dir=${dest_dir/h5/txt}
	touch ${dest_dir}
	./main.o $file > $dest_dir

	hf=$(grep "HF energy" $dest_dir | grep -E -o "[+-]?[0-9]+.[0-9]+")
	mp2=$(grep "MP2 energy" $dest_dir | grep -E -o "[+-]?[0-9]+.[0-9]+")

	# echo $hf
	# echo $mp2
	hf_dev=$(echo "(${hf_ref[i]} - $hf)" | bc -l | awk '{printf ".6f"($1 >= 0) ? $1 : -$1}')
	mp2_dev=$(echo "(${mp2_ref[i]} - $mp2)" | bc -l | awk '{printf ".6f"($1 >= 0) ? $1 : -$1}')
	if (( $(echo "$hf_dev < 0.00001" | bc -l) ))&&(( $(echo "$mp2_dev < 0.000001" | bc -l) )); then
		echo "Test on $file Succeeded"
	else
		echo "Test on $file Failed"
	fi
	# echo "$hf_dev"
	# echo "$mp2_dev"
done
