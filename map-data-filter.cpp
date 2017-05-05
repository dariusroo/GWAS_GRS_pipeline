#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main (){

	string mapfilename, datafilename, newdatafilename;
	ifstream mapfile, datafile;
	ofstream newdatafile;

	cin >> mapfilename >> datafilename >> newdatafilename;

	string line1, line2;
	int n = 0;
	int d = 0;

	mapfile.open(mapfilename.c_str());

	while(getline(mapfile, line1)){
		n++;
	}

	mapfile.close();

	datafile.open(datafilename.c_str());

	while(getline(datafile, line2)){
		d++;
	}

	datafile.close();

	int mchr[n], mposID[n], dchr[n], dposID[n], dc3[n];
	char mref[n], malt[n];
	double mmaf[n], mcall[n], mrsq[n];
	string dc2[n];
	int i = 0;

	datafile.open(datafilename.c_str());

	getline(datafile, line1);

	for (i = 0; i < d-1; i++){
		datafile >> mchr[i] >> mposID[i] >> mref[i] >> malt[i] >> mmaf[i] >> mcall[i] >> mrsq[i];
	}

	datafile.close();

	mapfile.open(mapfilename.c_str());

	for (i = 0; i < n; i++){
		mapfile >> dchr[i] >> dc2[i] >> dc3[i] >> dposID[i];
	}

	mapfile.close();

	newdatafile.open(newdatafilename.c_str());

	int j = 0;

	for (i = 0; i < n; i++){
		for (j = 0; j < d-1; j++){
			if ((dposID[i] == mposID[j]) || (dposID[i] == (mposID[j]+1))){
				newdatafile << mposID[j] << "\t" <<  mref[j] << "\t" <<  malt[j] << endl;
			}
		}
	}

	return 0;

}
