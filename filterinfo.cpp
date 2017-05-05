#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main (){

	int N = 1000;//this is the number of loci that are analyzed at the same time
	int M = 0;//number of SNPs in the info file
	int Z = 0;//number of SNPs to look for
	int i = 0;//counter
	int j = 0;//counter 		

	string chrnumber;

	/* infofile are the .info files output of the imputation
 	readfile is the same as infofile
	snpsfile is the file with the selected SNPs
	outfile is the designated output file */
	string infofilename, snpsfilename, outfilename;
	ifstream infofile, readfile, snpsfile;
	ofstream outfile;

	cin >> chrnumber >> infofilename >> snpsfilename >> outfilename;//chromosome number and filename output stream

	infofile.open(infofilename.c_str());

	string line1;

	while(getline(infofile, line1)){//reads the number of lines in the info file
		M++;
	}	

	infofile.close();

	snpsfile.open(snpsfilename.c_str());

	string line2;

	while(getline(snpsfile, line2)){//reads the number of selected SNPs
		Z++;
	}

	snpsfile.close();

	string chr[Z], refID[Z], refID2[Z], rsID[Z], modrefID[Z], modrefID2[Z];
	//refID = position ID
	//refID2 = position ID + 1 base pair
	//rsID = SNP name (usually rs#)
	//mod variables have the ":" to concatenate the chromosome number to the position ID

	snpsfile.open(snpsfilename.c_str());

	for (i = 0; i < Z; i++){

		snpsfile >> chr[i] >> refID[i] >> refID2[i] >> rsID[i];//inputs the SNP file info into the array
	}

	snpsfile.close();

	for (i = 0; i < Z; i++){//concatenates the chr# to the position ID

		modrefID[i] = chrnumber+":"+refID[i];
		modrefID2[i] = chrnumber+":"+refID2[i];

	}

	int X = M/N;//chunks the number of info-file lines to prevent memory overload

	string snp[N], geno[N], loorsq[N], empr[N], emprsq[N], dose0[N], dose1[N];
	char ref[N], alt[N];
	double altfrq[N], maf[N], avgcall[N], rsq[N];
	/*these are all different values in the info file*/

	readfile.open(infofilename.c_str());

	outfile.open(outfilename.c_str());

	outfile << "Chr\tPosID\tA1\tA2\tMAF\tAvgCall\trsq" << endl;//writes header to the ouptut

	string word;//temporary variable
	getline(readfile, word);//skips first line

	outfile << fixed << showpoint;
	outfile << setprecision(6);

	for (j = 0; j < X; j++){//chunk 1 -> chunk 2 -> chunk 3 -> etc

		for (i = 0; i < N; i++){//scans through the chunk

			readfile >> snp[i] >> ref[i] >> alt[i] >> altfrq[i] >> maf[i] >> avgcall[i] >> rsq[i] >> geno[i] >> loorsq[i] >> empr[i] >> emprsq[i] >> dose0[i] >> dose1[i];
			//assigns the values to their respective arrays
				
				for (int k = 0; k < Z; k++){//checks to see if selected SNP matches the one in the info file
					if (modrefID[k] == snp[i] || modrefID2[k] == snp[i]){//if there's a match, outputs the information metric for that SNP
						outfile << chrnumber << "\t" << refID[k] << "\t" << ref[i] << "\t" << alt[i] << "\t" << maf[i] << "\t" << avgcall[i] << "\t" << rsq[i] << endl;
					}
				}	
		}
	}	

	readfile.close();

	outfile.close();

	return 0;
}
