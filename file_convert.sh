#! /bin/sh
# the file convert bash script


# Script by Chong Chen [chong.chen@unlv.edu]
# Version 0.1; wor with GNU-awk 3.1.7 (will still work with eariler version)

#number of lines for correct chr1-data.txt file, set it manually 
target=6
for idx in {1..22}
do

read ln filename <<< $(wc -l chr$idx-data.txt)
if [ "$ln" -ne "$target" ]; then
	echo "chr-data.txt line number is incorrect, should be $target lines"
	exit
fi

#set the value of threshold manually
thres=0.9

IFS=" " read -r -a list <<< $(awk -v th="$thres" '{if($7<th) print NR; }' chr$idx-data.txt) 

#echo ${list[0]}
#count number
count=0
while [ "x${list[count]}" != "x" ]
do
   count=$(( $count + 1 ))
done
#echo $count
ln=0;
#delete line of chr1-markers.map
while [ $ln -lt $count ]
do
	if [ "$ln" -eq "0" ]; then
		awk -v del_n="${list[$ln]}" '{if(NR+1!=del_n) print;}' chr$idx-markers.map > chr$idx-markers.map.txt	
		awk -v del_c="${list[$ln]}" 'BEGIN {del_c1=(del_c-2)*2+7;} \
		{for (i=7;i<del_c1;++i) {printf $i " "} for(i=del_c1+2;i<17;++i) {printf $i " "} printf "\n"}' \
		chr$idx-markers.ped > chr$idx-markers.ped.txt
	else
		del_idx=$((${list[$ln]}-$ln));
		end_c=$(($target*2-2-2*$ln))
		echo "delete line $del_idx with end_c $end_c"
		awk -v del_n="$del_idx" '{if(NR+1!=del_n) print;}' chr$idx-markers.map.txt > chr$idx-markers.map.txt.new \
		&& rm chr$idx-markers.map.txt && mv chr$idx-markers.map.txt.new chr$idx-markers.map.txt
		awk -v del_c="$del_idx" -v end="$end_c" 'BEGIN {del_c1=(del_c-2)*2+1;} \
		{ for(i=1;i<del_c1;++i) {printf $i " "} for(i=del_c1+2;i<=end;++i) {printf $i " "} printf "\n"}' \
		chr$idx-markers.ped.txt >chr$idx-markers.ped.txt.new \
		&& rm chr$idx-markers.ped.txt && mv chr$idx-markers.ped.txt.new chr$idx-markers.ped.txt
		#echo "ln is $ln new bias is  $((${list[ln]} - ${list[$ln-1]}))"
		#awk -v del_n="$((${list[$ln]}-${list[$ln-1]}"
	fi;
	ln=$(( $ln + 1 )) 
done

if [ "$count" -eq "0" ]; then
for idx in {1..22}
do
	cp chr$idx-markers.map chr$idx-markers.map.txt
	cp chr$idx-markers.ped chr$idx-markers-temp.ped.txt
	python ped-text.py --input chr$idx-markers-temp.ped.txt --output chr$idx-markers.ped.txt
	rm chr$idx-markers-temp.ped.txt
done

fi;
#awk -v del_n="$a" '{if(NR+1!=del_n) print;}' chr$idx-markers.map > chr$idx-markers.map.txt 

#delete columns of chr1-markers.ped
#awk -v del_c="$a" 'BEGIN {del_c1=(del_c-2)*2+7;} \
#{for (i=7;i<del_c1;++i) {printf $i " "} for(i=del_c1+2;i<17;++i) {printf $i " "} printf "\n"}' \
#chr$idx-markers.ped> chr$idx-markers.ped.txt

done
