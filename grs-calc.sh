#!/bin/bash
#Outputs info metric for each SNP

for i in {1..22}
do
perl -p -i -e "s/\r//g" chr$i-markers.ped.txt
./uw-analysis.out << EOF
chr$i-markers.ped.txt
chr$i-alleles.txt
chr$i-scores.txt
EOF
done
