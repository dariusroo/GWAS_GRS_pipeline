#!/bin/bash

for i in {1..22}
do
if [[ -s chr$i-scores.txt ]]; then
./score-append.out << EOF
chr$i-scores.txt
EOF
fi;
done
./score-columns.out
