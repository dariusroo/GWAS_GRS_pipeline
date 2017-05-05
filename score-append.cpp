#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main (){

	string scorefilename, line;
	ifstream scorefile, combinefile;
	ofstream outfile;

	cin >> scorefilename;

	int N = 0;
	int i = 0;

	scorefile.open(scorefilename.c_str());
	
	while(getline(scorefile, line)){
		N++;
	}

	scorefile.close();

	double scores[N];
	double combined[N];

	combinefile.open("combined-rows.txt");

	for (i = 0; i < N; i++){
		combinefile >> combined[i];
	}

	scorefile.open(scorefilename.c_str());

	for (i = 0; i < N; i++){
		scorefile >> scores[i];
		scores[i] = scores[i] + combined[i]; 
	}

	scorefile.close();

	outfile.open("combined-rows.txt");

	for (i = 0; i < N; i++){
		outfile << scores[i] << " ";
	}

	outfile.close();

	return 0;
}
