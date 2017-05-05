#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main (){

	ifstream scorefile;
	ofstream outfile;

	int i = 0;
	int N = 0;
	string line;

	scorefile.open("combined-rows.txt");

	getline(scorefile, line);

	N = line.length();

	scorefile.close();

	double scores[N];

	scorefile.open("combined-rows.txt");

	for (i = 0; i < N; i++){
		scorefile >> scores[i];
	}

	scorefile.close();

	outfile.open("combined-scores.txt");

	for (i = 0; i < N; i++){
		outfile << scores[i] << endl;
	}

	outfile.close();

	return 0;
}
