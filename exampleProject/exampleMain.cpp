#include<iostream>
#include"options.h"

using namespace std;
using namespace DHBW_Programmieren;

class Klasse : public Beispiel_XML{

public:

void ParseXML(bool b){
	cout << "Example implementation of external Method" << endl;
}

void printVersion(int a){
	cout << "Example implementation of external Method" << endl;
}

};

int main(int argc, char *argv[]){

	Klasse k;
	k.parseOptions(argc, argv);
}