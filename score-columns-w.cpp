#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main (){

	ifstream scorefile;
	ofstream outfile;
	string suffix;

	cin >> suffix;

	int i = 0;
	int N = 0;
	string line;

	string scorefilename = "combined-rows-"+suffix+".txt";

	scorefile.open(scorefilename.c_str());

	getline(scorefile, line);

	N = line.length();

	scorefile.close();

	double scores[N];

	scorefile.open(scorefilename.c_str());

	for (i = 0; i < N; i++){
		scorefile >> scores[i];
	}

	scorefile.close();

	string outfilename = "combined-scores-"+suffix+".txt";

	outfile.open(outfilename.c_str());

	for (i = 0; i < N; i++){
		outfile << scores[i] << endl;
	}

	outfile.close();

	return 0;
}
