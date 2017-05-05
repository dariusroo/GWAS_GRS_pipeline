Version 1.1, April 27, 2017
By Darius Roohani and Chong Chen
This pipeline is designed to calculate weighted and unweighted risk scores from files outputted by the Michigan Imputation Server.

Software requirements:
-PLINK 1.9 or above
-Python 2.7 or above

The pipeline also uses a Perl command.

This pipeline requires the following files:
-chr1.dose.vcf.gz, chr2.dose.vcf.gz, ... , chr22.dose.vcf.gz
-chr1.info.gz, chr2.info.gz , ... , chr22.info.gz
-chr1-snps.txt, chr2-snps.txt, ... , chr22-snps.txt

These must all be in the same directory, and must have those exact names.

The first two file sets are provided by the server. The last file set will be one you have to create. Here is the proper formatting:

chr#	position ID	positionID + 1	rsID

An example file looks like:

6       151907747       151907748       rs04869742
6       151946657       151946658       rs07751941
6       21384612        21384613        rs09466056
6       44639183        44639184        rs11755164
6       127167071       127167072       rs13204965

There is no header. The position IDs MUST be from the GRCh37 genome assembly. Check your literature values to see what assembly your position IDs are in; if they are in another assembly, use the UCSC LiftOver program to convert it to the Ch37 assembly (https://genome.ucsc.edu/cgi-bin/hgLiftOver). If there are no SNPs you want to analyze in a certain chromosome, there is no need to create the -snps.txt file for it.

To run the pipeline, simply type the command:
./pipeline.sh

The pipeline will output your final scores as "combined-scores.txt".

If you wish to calculated weighted risk scores, you will need to copy your chr#-alleles.txt file to chr#-alleles-SUFFIX.txt, where the SUFFIX is any name you specify. Each of these files MUST have the same suffix.

Open each chr#-alleles-SUFFIX.txt file and after the third column, tab and put in your beta values. If your beta value is NEGATIVE, swap the alleles in that row. The second column of the file is the reference allele, the third column is the alternate allele.

To calculate your weighted risk score, type the command:
./weighted-score.sh

And when it prompts you for the suffix, type the one you used and press enter (it is case-sensitive).

This script will output your final scores as "combined-scores-SUFFIX.txt"
