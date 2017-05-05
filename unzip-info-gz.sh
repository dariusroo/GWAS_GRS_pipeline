#!/bin/sh
#Unzips info files

for i in {1..22}
do
	gunzip chr$i.info.gz
done
