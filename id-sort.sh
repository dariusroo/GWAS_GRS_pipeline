#!/bin/bash

for i in {1..22}

do

	python txt-csv.py --input chr$i-markers-unsorted.ped --output chr$i-markers.csv
	python csv-sort.py --input chr$i-markers.csv --output chr$i-markers.ped

done
