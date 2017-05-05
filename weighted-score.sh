#!/bin/bash
echo "What is the suffix of your allele file containing beta values? (chr6-alleles-???.txt)"
read suffix
echo "Calculating weighted risk scores..."
echo "----------"
for i in {1..22}
do
./w-analysis.out << EOF
chr$i-markers.ped.txt
chr$i-alleles-$suffix.txt
chr$i-scores-$suffix.txt
EOF
done
for i in {1..22}
if [[ -s chr$i-scores-$suffix.txt ]]; then
do
./score-append-w.out << EOF
chr$i-scores-$suffix.txt
$suffix
EOF
done
fi;
./score-columns-w.out << EOF
$suffix
EOF
echo "Weighted scores written to combined-scores-$suffix.txt"
