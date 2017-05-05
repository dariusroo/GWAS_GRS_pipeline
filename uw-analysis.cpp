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

	string rs1, rs2;
	int num1, num2, num3, num4;

	ptfile.open(ptfilename.c_str());

	string line1, line2;

	while(getline(ptfile, line1)){//gets the number of lines (which is equal to the number of patients) in the genotype file
		pt++;
	}

	ptfile.close();
	
	while(getline(locifile,line2)){//gets the number of lines (which is equal to the number of SNPs) in the map file
		N++;
	}

	locifile.close();*/

	int i = 0;//counters
	int j = 0;

	for (i = 0; i < pt; i++){//scans through patients

		for (j = 0; j < N; j++){//scans through the genotypes of each patient and assigns them to an array

			ptfile >> a1[i][j] >> a2[i][j];
		}

	}

	ptfile.close();*/

	allelefile.open(allelefilename.c_str());

	while(getline(allelefile, line2)){
		N++;
	}

	allelefile.close();

	char a1[pt][N], a2[pt][N];
	char c1[N], refA[N];//array with affect allele value
	int pos[N];

	ptfile.open(ptfilename.c_str());

        for (i = 0; i < pt; i++){//scans through patients

                for (j = 0; j < N; j++){//scans through the genotypes of each patient and assigns them to an array

                        ptfile >> a1[i][j] >> a2[i][j];
                }

        }

        ptfile.close();

	allelefile.open(allelefilename.c_str());

	for (i = 0; i < N; i++){//scans through allele file and assigns the affect allele and beta values to the arrays
		allelefile >> pos[i] >> c1[i] >> refA[i];
	}

	allelefile.close();

	char temp1, temp2, reftemp;
	int unweighted = 0;
	int score[pt];
	/*these are the output variables -- temporary or self-explanatory*/

	for (i = 0; i < pt; i++){//scans through each patient

		for (j = 0; j < N; j++){//scans through each SNP
			
			temp1 = a1[i][j];
			temp2 = a2[i][j];
			reftemp = refA[j];

			if (temp1 == reftemp){//if patient's first allele = affect allele
				unweighted++;//increase unweighted score by 1 if it is a BMD-lowering allele
			}
			if (temp2 == reftemp){//same as above, except if patient's second allele = affect allele
				unweighted++;
			}
		}
		score[i] = unweighted;//assigns the scores
		unweighted = 0;
	}

	ofstream scores;

	scores.open(scoresfilename.c_str());
	
	for (i = 0; i < pt; i++){//outputs the scores to the designated output file
		scores << score[i] << endl;
	}

	scores.close();

	return 0;

}
