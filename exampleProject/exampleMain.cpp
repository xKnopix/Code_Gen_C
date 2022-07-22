#include<iostream>
#include"options.h"

using namespace std;
using namespace DHBW_Programmieren;

///Diese Klasse erbt vonBeispiel_XML , hier können die Externen Methoden ueberschrieben werden
class Klasse : public Beispiel_XML{

public:

void ParseXML(bool b){///Die Methode wird vererbt und soll ueberschrieben werden
	cout << "Example implementation of external Method" << endl;
}

void printVersion(int a){///Die Methode wird vererbt und soll ueberschrieben werden
	cout << "Example implementation of external Method" << endl;
}

};

int main(int argc, char *argv[]){

	Klasse k;
	k.parseOptions(argc, argv);
}