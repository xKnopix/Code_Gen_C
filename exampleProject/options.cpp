#include <string>
#include <iostream>
#include <vector>
#include "options.h"
using namespace std;
namespace DHBW_Programmieren
{
void Beispiel_XML::myPrint(string myString, int newLineChecker)
{
int lineLength = newLineChecker;
for (auto i = 0; i != myString.size(); ++i)
{
if (i == newLineChecker)
{
newLineChecker += lineLength;
cout << endl;
}
cout << myString[i];
}
}
bool Beispiel_XML::isSetastylepath()
{
return isSetastylepathBool;
}
string Beispiel_XML::getValueOfastylepath()
{
return astylepathParam;
}
void Beispiel_XML::printHelp(int signPerLine)
{
cout<<""<< endl;
myPrint("--astyle-path\n", getValueOfsignperline());
myPrint("  Der Pfad wo die Astyle executable gefunden werden kann\n\n", getValueOfsignperline());
myPrint("-h, --help\n", getValueOfsignperline());
myPrint("  \n\n", getValueOfsignperline());
myPrint("-n, --only-if-newer\n", getValueOfsignperline());
myPrint("  Generiert nur wenn die Eingangsdatei neuer ist wie die bereits generierte\n\n", getValueOfsignperline());
myPrint("--no-format\n", getValueOfsignperline());
myPrint("  Erzeugte Datei wird nicht formatiert\n\n", getValueOfsignperline());
myPrint("--out-path\n", getValueOfsignperline());
myPrint("  Der Pfad wo das Ergebnis hingenriert werden soll (sonst ins aktuelle Verzeichnis)\n\n", getValueOfsignperline());
myPrint("--parse-only\n", getValueOfsignperline());
myPrint("  Parst die Datei einmal und beendet das Programm\n\n", getValueOfsignperline());
myPrint("--sign-per-line\n", getValueOfsignperline());
myPrint("  Die Anzahl der Zeichen pro Linie f�r den Helptext. Ohne Argument wird der Standartwert genommen.\n\n", getValueOfsignperline());
myPrint("--v\n",  getValueOfsignperline());
myPrint("  Gibt die Version des Programms aus und beendet\n\n", getValueOfsignperline());
myPrint("\n", getValueOfsignperline());myPrint("Sample Usage:\n", getValueOfsignperline());myPrint("getoptgen [options] ... QUELLE\n", getValueOfsignperline());myPrint("getoptgen [--out-path] ... QUELLE\n", getValueOfsignperline());myPrint("\n", getValueOfsignperline());myPrint("Overall-Description:\n", getValueOfsignperline());myPrint("Erstellt einen Rumpf zum einlesen von Argumenten aus der Kommandozeile.\n", getValueOfsignperline());myPrint("Es kann sowohl mit innenliegenden Container wie externer Klassenanbindung eine Datenhaltung erfolgen.\n", getValueOfsignperline());myPrint("Sobald ein Methodenaufruf abstrakt ist, wird die Basisklasse abstrakt.\n", getValueOfsignperline());myPrint("Fuer die Formatierung der generierten Dateien wird astyle verwendet.\n", getValueOfsignperline());myPrint("\n", getValueOfsignperline());myPrint("Author Name: Michael Hornstein, Jacob Hochbaum, Johannes M�ssig, Jakob Irle, Linus Fallert, ", getValueOfsignperline());
myPrint("Author Mail: Michael.hornstein9@icloud.com, ", getValueOfsignperline());
myPrint("Author Phone: \n", getValueOfsignperline());
}
bool Beispiel_XML::isSetonlyifnewer()
{
return isSetonlyifnewerBool;
}
bool Beispiel_XML::isSetnoformat()
{
return isSetnoformatBool;
}
bool Beispiel_XML::isSetoutpath()
{
return isSetoutpathBool;
}
string Beispiel_XML::getValueOfoutpath()
{
return outpathParam;
}
bool Beispiel_XML::isSetparseonly()
{
return isSetparseonlyBool;
}
bool Beispiel_XML::getValueOfparseonly()
{
if(parseonlyParam == "true" || parseonlyParam == "1")
{
parseonlyBool = true;
}
else if(parseonlyParam == "false" || parseonlyParam == "0")
{
   parseonlyBool = false;
}
else
{
cerr << "bool wurde nicht im korrekten Format angegeben, erlaubt ist [true/1][false/0]! " << endl;
}
return parseonlyBool;
}
bool Beispiel_XML::isSetsignperline()
{
return isSetsignperlineBool;
}
int Beispiel_XML::getValueOfsignperline()
{
try {
                signperlineInt = stol(signperlineParam);
            }
            catch (invalid_argument const &e) {
                cerr << "Bad input: invalid_argument thrown for signperline, using default Value if given" << endl;
            }
            catch (out_of_range const &e) {
                cerr << "Integer overflow: out_of_range thrown for signperline, using default Value if given" << endl;
            }return signperlineInt;
}
bool Beispiel_XML::isSetversion()
{
return isSetversionBool;
}
void Beispiel_XML::unknownOption(const string& unknown_option)
{
	cout << "Unbekannter Parameter '" + unknown_option + "'!" << endl;
exit(EXIT_SUCCESS);
}
void Beispiel_XML::parseOptions(int argc, char* argv[])
{
vector<int> exclusions;
int exitArg = 0;
int noRef = -1;
string refValues[63];
vector<string> additionalParams;
vector<string> argumentnames;
vector<string> refValuesSorted;
vector<vector<string>> exclusionValuesSorted;
string astylepathStr;
bool boolIsSetastylepath;
string outpathStr;
bool boolIsSetoutpath;
string parseonlyStr;
string signperlineStr = "79";
for(int i = 1; i<argc; i++)
{
if(string(argv[i]) == "--astyle-path")
{
vector<string> localExclusions = {"1", "2", "3"};
for (int m = 0; m < localExclusions.size(); m++)
{for(int k = 0; k < refValuesSorted.size(); k++)
{if(refValuesSorted[k] == localExclusions[m])
{cout << "--astylepath ist nicht erlaubt mit " + argumentnames[k];
exit(EXIT_FAILURE);
}
}
}exclusionValuesSorted.push_back(localExclusions);
argumentnames.push_back("--astylepath");
refValuesSorted.push_back("x");
if(i+1 < argc)
{
astylepathStr = argv[i+1];
}
else
{cout << "--astyle-path benötigt ein zusätzliches Argument!\n"
"" << endl;
exit(EXIT_FAILURE);

cerr << "ERROR: --astyle-path benötigt ein zusätzliches Argument!\n"
"" << endl;
exit(EXIT_FAILURE);
}
additionalParams.push_back(astylepathStr);
}
if(string(argv[i]) == "-h" || string(argv[i]) == "--help")
{for(int r = 0; r < exclusionValuesSorted.size(); r++)
{vector<string> temp = exclusionValuesSorted[r];
for(int q = 0; q < temp.size(); q++){
if(to_string(1) == temp[q])
{cout << "--help ist nicht erlaubt mit " + argumentnames[r] << endl;exit(EXIT_FAILURE);
}}

}
vector<string> tempVec = {"x"};
refValuesSorted.push_back(to_string(1));
exclusionValuesSorted.push_back(tempVec);
argumentnames.push_back("--help");

}if(string(argv[i]) == "-n" || string(argv[i]) == "--only-if-newer")
{
vector<string> localExclusions = {"1", "2", "3"};
for (int m = 0; m < localExclusions.size(); m++)
{for(int k = 0; k < refValuesSorted.size(); k++)
{if(refValuesSorted[k] == localExclusions[m])
{cout << "--onlyifnewer ist nicht erlaubt mit " + argumentnames[k];
exit(EXIT_FAILURE);
}
}
}exclusionValuesSorted.push_back(localExclusions);
argumentnames.push_back("--onlyifnewer");
refValuesSorted.push_back("x");

}if(string(argv[i]) == "--no-format")
{
vector<string> localExclusions = {"1", "2", "3"};
for (int m = 0; m < localExclusions.size(); m++)
{for(int k = 0; k < refValuesSorted.size(); k++)
{if(refValuesSorted[k] == localExclusions[m])
{cout << "--noformat ist nicht erlaubt mit " + argumentnames[k];
exit(EXIT_FAILURE);
}
}
}exclusionValuesSorted.push_back(localExclusions);
argumentnames.push_back("--noformat");
refValuesSorted.push_back("x");

}if(string(argv[i]) == "--out-path")
{
vector<string> localExclusions = {"1", "2", "3"};
for (int m = 0; m < localExclusions.size(); m++)
{for(int k = 0; k < refValuesSorted.size(); k++)
{if(refValuesSorted[k] == localExclusions[m])
{cout << "--outpath ist nicht erlaubt mit " + argumentnames[k];
exit(EXIT_FAILURE);
}
}
}exclusionValuesSorted.push_back(localExclusions);
argumentnames.push_back("--outpath");
refValuesSorted.push_back("x");
if(i+1 < argc)
{
outpathStr = argv[i+1];
}
else
{cout << "--out-path benötigt ein zusätzliches Argument!\n"
"" << endl;
exit(EXIT_FAILURE);

cerr << "ERROR: --out-path benötigt ein zusätzliches Argument!\n"
"" << endl;
exit(EXIT_FAILURE);
}
additionalParams.push_back(outpathStr);
}
if(string(argv[i]) == "--parse-only")
{
vector<string> localExclusions = {"1", "2"};
for (int m = 0; m < localExclusions.size(); m++)
{for(int k = 0; k < refValuesSorted.size(); k++)
{if(refValuesSorted[k] == localExclusions[m])
{cout << "--parseonly ist nicht erlaubt mit " + argumentnames[k];
exit(EXIT_FAILURE);
}
}
}exclusionValuesSorted.push_back(localExclusions);
argumentnames.push_back("--parseonly");
for (int j = 0; j < exclusionValuesSorted.size(); j++)
{vector<string> tempExclusionVec = exclusionValuesSorted[j];for (int k = 0; k < tempExclusionVec.size(); k++)
{if (" 3" == tempExclusionVec[k])
{cout << "--parseonly ist nicht erlaubt mit " + argumentnames[j];
exit(EXIT_FAILURE);
}
}
}vector<string> temp = {"3"};
refValuesSorted.push_back(to_string(3));
if(i+1 < argc)
{
parseonlyStr = argv[i+1];
}
else
{cout << "--parse-only benötigt ein zusätzliches Argument!\n"
"" << endl;
exit(EXIT_FAILURE);

cerr << "ERROR: --parse-only benötigt ein zusätzliches Argument!\n"
"" << endl;
exit(EXIT_FAILURE);
}
additionalParams.push_back(parseonlyStr);
}
if(string(argv[i]) == "--sign-per-line")
{
vector<string> localExclusions = {"1", "2", "3", "63"};
for (int m = 0; m < localExclusions.size(); m++)
{for(int k = 0; k < refValuesSorted.size(); k++)
{if(refValuesSorted[k] == localExclusions[m])
{cout << "--signperline ist nicht erlaubt mit " + argumentnames[k];
exit(EXIT_FAILURE);
}
}
}exclusionValuesSorted.push_back(localExclusions);
argumentnames.push_back("--signperline");
refValuesSorted.push_back("x");
if(i+1 < argc)
{
signperlineStr = argv[i+1];
}
additionalParams.push_back(signperlineStr);
}
if(string(argv[i]) == "-v")
{
vector<string> localExclusions = {"1", "3"};
for (int m = 0; m < localExclusions.size(); m++)
{for(int k = 0; k < refValuesSorted.size(); k++)
{if(refValuesSorted[k] == localExclusions[m])
{cout << "--version ist nicht erlaubt mit " + argumentnames[k];
exit(EXIT_FAILURE);
}
}
}exclusionValuesSorted.push_back(localExclusions);
argumentnames.push_back("--version");
for (int j = 0; j < exclusionValuesSorted.size(); j++)
{vector<string> tempExclusionVec = exclusionValuesSorted[j];for (int k = 0; k < tempExclusionVec.size(); k++)
{if (" 2" == tempExclusionVec[k])
{cout << "--version ist nicht erlaubt mit " + argumentnames[j];
exit(EXIT_FAILURE);
}
}
}vector<string> temp = {"2"};
refValuesSorted.push_back(to_string(2));

}}
if(!astylepathStr.empty() && astylepathStr.length() > 1)
{
if((astylepathStr.at(0) == '-') || astylepathStr.length() <= 1)
{
cout << "--astyle-path benötigt ein zusätzliches Argument!\n Da der nächste Parameter mit einem '-' startet, oder zu kurz (<1) ist, wurde kein zusaetzliches Argument erkannt!"
"" << endl;
cerr << "ERROR: --astyle-path benötigt ein zusätzliches Argument!\n Da der nächste Parameter mit einem '-' startet, oder zu kurz (<1) ist, wurde kein zusaetzliches Argument erkannt!"
"" << endl;
exit(EXIT_FAILURE);
}
}
if(!outpathStr.empty() && outpathStr.length() > 1)
{
if((outpathStr.at(0) == '-') || outpathStr.length() <= 1)
{
cout << "--out-path benötigt ein zusätzliches Argument!\n Da der nächste Parameter mit einem '-' startet, oder zu kurz (<1) ist, wurde kein zusaetzliches Argument erkannt!"
"" << endl;
cerr << "ERROR: --out-path benötigt ein zusätzliches Argument!\n Da der nächste Parameter mit einem '-' startet, oder zu kurz (<1) ist, wurde kein zusaetzliches Argument erkannt!"
"" << endl;
exit(EXIT_FAILURE);
}
}
if(!parseonlyStr.empty() && parseonlyStr.length() > 1)
{
if((parseonlyStr.at(0) == '-') || parseonlyStr.length() <= 1)
{
cout << "--parse-only benötigt ein zusätzliches Argument!\n Da der nächste Parameter mit einem '-' startet, oder zu kurz (<1) ist, wurde kein zusaetzliches Argument erkannt!"
"" << endl;
cerr << "ERROR: --parse-only benötigt ein zusätzliches Argument!\n Da der nächste Parameter mit einem '-' startet, oder zu kurz (<1) ist, wurde kein zusaetzliches Argument erkannt!"
"" << endl;
exit(EXIT_FAILURE);
}
}
if(!signperlineStr.empty() && signperlineStr.length() > 1)
{
if((signperlineStr.at(0) == '-' && signperlineStr.at(1) == '-') || signperlineStr.length() <= 1)
{
cout << "zu --sign-per-line wurde kein zusätzliches Argument übergeben, default-Wert: 79 wird übernommen!"<< endl;
}
}
try
{
signperlineInt = stol(signperlineParam);
}
catch (invalid_argument const &e)
{
cout << "Bad input: invalid_argument thrown for sign-per-line, using default Value if given" << endl;
cerr << "Bad input: invalid_argument thrown for sign-per-line, using default Value if given" << endl;
}
catch (out_of_range const &e)
{
cout << "Integer overflow: out_of_range thrown for sign-per-line, using default Value if given" << endl;
cerr << "Integer overflow: out_of_range thrown for sign-per-line, using default Value if given" << endl;
}
if(exitArg > 0)
{
cout << "EXIT" << endl;
return;
}
for(int i = 1; i<argc; i++)
{
if(string(argv[i]) == "--astyle-path")
{
cout << "Es wurde der Parameter --astyle-path erfolgreich übergeben!" << endl;
isSetastylepathBool = true;
astylepathParam = astylepathStr;
cout << "Zusätzliche Argumente:" << getValueOfastylepath() << endl;
isSetastylepathBool = true;
continue;}
if(string(argv[i]) == "-h" || string(argv[i]) == "--help")
{
printHelp(signperlineInt);
continue;}
if(string(argv[i]) == "-n" || string(argv[i]) == "--only-if-newer")
{
cout << "Es wurde der Parameter --only-if-newer erfolgreich übergeben!" << endl;
isSetonlyifnewerBool = true;
continue;}
if(string(argv[i]) == "--no-format")
{
cout << "Es wurde der Parameter --no-format erfolgreich übergeben!" << endl;
isSetnoformatBool = true;
continue;}
if(string(argv[i]) == "--out-path")
{
cout << "Es wurde der Parameter --out-path erfolgreich übergeben!" << endl;
isSetoutpathBool = true;
outpathParam = outpathStr;
cout << "Zusätzliche Argumente:" << getValueOfoutpath() << endl;
isSetoutpathBool = true;
continue;}
if(string(argv[i]) == "--parse-only")
{
cout << "Es wurde der Parameter --parse-only erfolgreich übergeben!" << endl;
isSetparseonlyBool = true;
parseonlyParam = parseonlyStr;
cout << "Zusätzliche Argumente:" << getValueOfparseonly() << endl;
isSetparseonlyBool = true;
ParseXML(parseonlyBool);
continue;}
if(string(argv[i]) == "--sign-per-line")
{
cout << "Es wurde der Parameter --sign-per-line erfolgreich übergeben!" << endl;
isSetsignperlineBool = true;
signperlineParam = signperlineStr;
cout << "Zusätzliche Argumente:" << getValueOfsignperline() << endl;
isSetsignperlineBool = true;
continue;}
if(string(argv[i]) == "-v")
{
cout << "Es wurde der Parameter -- erfolgreich übergeben!" << endl;
isSetversionBool = true;
printVersion(versionInt);
continue;}
int temp = 0;for(int m = 0; m < additionalParams.size(); m++){   if(additionalParams[m] == argv[i])
{
temp = 1;
}
}if(temp == 1)
{continue;
}
unknownOption(argv[i]);}
}
}
