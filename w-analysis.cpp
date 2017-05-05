#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main (){

	int pt = 0; //number of patients
	int N = 0; //number of loci/SNPs

	/* ptfile contains all G, T, A, C's for every SNP (genotype file), one row is one patient. 
  	allelefile contains every allele with FN and LS beta values (respectively). 
	locifile is the combined map file (chr#, chr#:posID, 0, posID) */

	ifstream ptfile, allelefile;

	string ptfilename, allelefilename, scoresfilename; //these are the filenames for stream input. scoresfilename is the designated output file name.

	cin >> ptfilename >> allelefilename >> scoresfilename;

	string rs1, rs2, line1, line2;
	int num1, num2, num3, num4;

	ptfile.open(ptfilename.c_str());

	while(getline(ptfile, line1)){//gets the number of lines (which is equal to the number of patients) in the genotype file
		pt++;
	}

	ptfile.close();
	
	allelefile.open(allelefilename.c_str());

	while(getline(allelefile,line2)){//gets the number of lines (which is equal to the number of SNPs) in the map file
		N++;
	}

	allelefile.close();

	char a1[pt][N], a2[pt][N];//each arrays contains one allele per patient for every SNP

	int i = 0;//counters
	int j = 0;

	ptfile.open(ptfilename.c_str());

	for (i = 0; i < pt; i++){//scans through patients

		for (j = 0; j < N; j++){//scans through the genotypes of each patient and assigns them to an array

			ptfile >> a1[i][j] >> a2[i][j];
		}

	}

	ptfile.close();

	allelefile.open(allelefilename.c_str());

	int posID[N];
	char refA[N], alt[N];//array with affect allele value
	double refB[N];//arrays with beta values

	for (i = 0; i < N; i++){//scans through allele file and assigns the affect allele and beta values to the arrays
		allelefile >> posID[i] >> alt[i] >> refA[i] >> refB[i];
		if (refB[i] < 0){
			cout << "Warning: Cannot have negative beta values. Please flip your alleles." << endl;
			return 0;
		}
	}

	allelefile.close();

	char temp1, temp2, reftemp;
	double refBtemp;
	double tempscoreB = 0.0;
	double Bscore[pt];
	/*these are the output variables -- temporary or self-explanatory*/

	for (i = 0; i < pt; i++){//scans through each patient

		for (j = 0; j < N; j++){//scans through each SNP
			
			temp1 = a1[i][j];
			temp2 = a2[i][j];
			reftemp = refA[j];
			refBtemp = refB[j];

			if (temp1 == reftemp){//if patient's first allele = affect allele
				tempscoreB += refBtemp;//add beta value to FN score
			}
			if (temp2 == reftemp){//same as above, except if patient's second allele = affect allele
				tempscoreB += refBtemp;
			}
		}
		Bscore[i] = tempscoreB;
		tempscoreB = 0.0;//resets the values for the next patient
	}

	ofstream scores;

	scores.open(scoresfilename.c_str());
	
	for (i = 0; i < pt; i++){//outputs the scores to the designated output file
		scores << Bscore[i] << endl;
	}

	return 0;

}
