#include<iostream>
#include"options.h"

using namespace std;
using namespace DHBW_Programmieren;

///Diese Klasse erbt von Beispiel_XML, hier können die Externen Methoden überschrieben werden
class Klasse : public Beispiel_XML{

public:

///Diese Methode wird vererbt und soll die Version ausgeben. Sie wird aufgerufen, wenn --parse-only angegeben wird
void ParseXML(bool b){
	cout << "Example implementation of external Methode" << endl;
}
///Die Methode wird vererbt und soll die Version ausgeben. Sie wird aufgerufen, wenn -v angegeben wird
void printVersion(int a){
	cout << "Example implementation of external Methode" << endl;
}

};

int main(int argc, char *argv[]){

	Klasse k;
	k.parseOptions(argc, argv);
}