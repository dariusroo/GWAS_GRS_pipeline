#!/bin/bash

for i in {1..22}

do
	/data1/home/nipm/darius/bin/plink/plink --vcf chr$i.dose.vcf.gz --extract range chr$i-snps.txt --make-bed --out chr$i-markers-unsorted
	/data1/home/nipm/darius/bin/plink/plink --bfile chr$i-markers-unsorted --recode --tab --out chr$i-markers-unsorted
done
