#!/bin/bash
#Version 1.1, April 27 2017
#Scripts written by Darius Roohani and Chong Chen
echo "Unzipping info files..."
echo "----------"
./unzip-info-gz.sh
echo "Filtering out poorly imputed SNPs..."
echo "----------"
for i in {1..22}
do
./filterinfo.out << EOF
$i
chr$i.info
chr$i-snps.txt
chr$i-data.txt
EOF
done
echo "Extracting SNPs..."
echo "----------"
./plink-extract.sh
echo "Organizing files..."
echo "----------"
./map-mv.sh
./id-sort.sh
./file_convert.sh
for i in {1..22}
do
./map-data-filter.out << EOF
chr$i-markers.map.txt
chr$i-data.txt
chr$i-alleles.txt
EOF
done
echo "Calculating risk scores..."
echo "----------"
./grs-calc.sh
./score-sum.sh
rm *-unsorted*
echo "Unweighted risk scores written to combined-scores.txt"
