#include <string>
#include <iostream>
#include <vector>
#include "newFile.h"
using namespace std;
namespace noNameSpace
{
void noClassname::myPrint(string myString, int newLineChecker)
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
void noClassname::printHelp(int signPerLine)
{
cout<<""<< endl;
myPrint("-h, --help\n", signPerLine);
myPrint("Diese Hilfe ausgeben und beenden\n\n", 79);
myPrint("-v, --version\n", signPerLine);
myPrint("Gibt die Version des Programms aus und beendet\n\n", 79);
myPrint("--out-path\n", signPerLine);
myPrint("	Der Pfad wo das Ergebnis hingeneriert werden soll (sonst ins aktuelle Verzeichnis)\n\n", signPerLine);
myPrint("--astyle-path\n", signPerLine);
myPrint("	Der Pfad wo die Astyle executable gefunden werden kann\n\n", signPerLine);
myPrint("--sign-per-line\n", signPerLine);
myPrint("	Die Anzahl der Zeichen pro Linie fÃ¼r den Helptext. Ohne Argument wird der Standartwert genommen.\n\n", signPerLine);
myPrint("-n, --only-if-newer\n", signPerLine);
myPrint("Generiert nur wenn die Eingangsdatei neuer ist wie die bereits generierte\n\n", 79);
myPrint("--no-format\n", signPerLine);
myPrint("	Erzeugte Datei wird nicht formatiert\n\n", signPerLine);
myPrint("--parse-only\n", signPerLine);
myPrint("	Parst die Datei einmal und beendet das Programm\n\n", signPerLine);
myPrint("Author: anonymous\n", 79);
}
bool noClassname::isSetVersion()
{
return VersionBool;
}
bool noClassname::isSetoutpath()
{
return outpathBool;
}
string noClassname::getValueOfoutpath()
{
return outpathParam;
}
bool noClassname::isSetastylepath()
{
return astylepathBool;
}
string noClassname::getValueOfastylepath()
{
return astylepathParam;
}
bool noClassname::isSetsignperline()
{
return signperlineBool;
}
int noClassname::getValueOfsignperline()
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
bool noClassname::isSetonlyifnewer()
{
return onlyifnewerBool;
}
bool noClassname::isSetnoformat()
{
return noformatBool;
}
void noClassname::ParseXML(bool parseonlyBool)
{
cout << "Parst die Datei einmal und beendet das Programm" << endl;
}
void noClassname::unknownOption(const string& unknown_option)
{
	cout << "Unbekannter Parameter '" + unknown_option + "'!" << endl;
exit(EXIT_SUCCESS);
}
void noClassname::parse(int argc, char* argv[])
{
vector<int> exclusions;
int exitArg = 0;
int noRef = -1;
string refValues[63];
string outpathStr;
bool boolIsSetoutpath;
string astylepathStr;
bool boolIsSetastylepath;
string signperlineStr = "79";
string parseonlyStr;
for(int i = 1; i<argc; i++)
{
if(string(argv[i]) == "-h" || string(argv[i]) == "--help")
{
vector<string> localExclusions = {"2", "3"};
for(int i = 0; i < exclusions.size(); i++)
{
for(int j = 0; j < localExclusions.size(); j++)
{
if(to_string(exclusions[i]) == localExclusions[j])
{
cerr << "help und "<< refValues[exclusions[i]]<<" sind nicht zusammen erlaubt!" << endl;
exitArg = 1;
}
}
}
if(noRef == 1)
{
exitArg = 1;
}
if(exitArg != 1)
{
exclusions.push_back(1);
refValues[1] = "help";noRef = 1;
}
}
if(string(argv[i]) == "-v" || string(argv[i]) == "--version")
{
vector<string> localExclusions = {"1", "3"};
for(int i = 0; i < exclusions.size(); i++)
{
for(int j = 0; j < localExclusions.size(); j++)
{
if(to_string(exclusions[i]) == localExclusions[j])
{
cerr << "Version und "<< refValues[exclusions[i]]<<" sind nicht zusammen erlaubt!" << endl;
exitArg = 1;
}
}
}
if(noRef == 1)
{
exitArg = 1;
}
if(exitArg != 1)
{
exclusions.push_back(2);
refValues[2] = "Version";noRef = 1;
}
}
if(string(argv[i]) == "--out-path")
{
vector<string> localExclusions = {"1", "2", "3"};
for(int i = 0; i < exclusions.size(); i++)
{
for(int j = 0; j < localExclusions.size(); j++)
{
if(to_string(exclusions[i]) == localExclusions[j])
{
cerr << "OutputPath und "<< refValues[exclusions[i]]<<" sind nicht zusammen erlaubt!" << endl;
exitArg = 1;
}
}
}
if(noRef == 1)
{
exitArg = 1;
}
if(exitArg != 1)
{
noRef = 1;
}
if(i+1 != argc)
{
outpathStr = argv[i+1];
}
}
if(string(argv[i]) == "--astyle-path")
{
vector<string> localExclusions = {"1", "2", "3"};
for(int i = 0; i < exclusions.size(); i++)
{
for(int j = 0; j < localExclusions.size(); j++)
{
if(to_string(exclusions[i]) == localExclusions[j])
{
cerr << "AstylePath und "<< refValues[exclusions[i]]<<" sind nicht zusammen erlaubt!" << endl;
exitArg = 1;
}
}
}
if(noRef == 1)
{
exitArg = 1;
}
if(exitArg != 1)
{
noRef = 1;
}
if(i+1 != argc)
{
astylepathStr = argv[i+1];
}
}
if(string(argv[i]) == "--sign-per-line")
{
vector<string> localExclusions = {"1", "2", "3"};
for(int i = 0; i < exclusions.size(); i++)
{
for(int j = 0; j < localExclusions.size(); j++)
{
if(to_string(exclusions[i]) == localExclusions[j])
{
cerr << "SignPerLine und "<< refValues[exclusions[i]]<<" sind nicht zusammen erlaubt!" << endl;
exitArg = 1;
}
}
}
if(noRef == 1)
{
exitArg = 1;
}
if(exitArg != 1)
{
noRef = 1;
}
if(i+1 != argc)
{
signperlineStr = argv[i+1];
}
}
if(string(argv[i]) == "-n" || string(argv[i]) == "--only-if-newer")
{
vector<string> localExclusions = {"1", "2", "3"};
for(int i = 0; i < exclusions.size(); i++)
{
for(int j = 0; j < localExclusions.size(); j++)
{
if(to_string(exclusions[i]) == localExclusions[j])
{
cerr << "OnlyIfNewer und "<< refValues[exclusions[i]]<<" sind nicht zusammen erlaubt!" << endl;
exitArg = 1;
}
}
}
if(noRef == 1)
{
exitArg = 1;
}
if(exitArg != 1)
{
noRef = 1;
}
}
if(string(argv[i]) == "--no-format")
{
vector<string> localExclusions = {"1", "2", "3"};
for(int i = 0; i < exclusions.size(); i++)
{
for(int j = 0; j < localExclusions.size(); j++)
{
if(to_string(exclusions[i]) == localExclusions[j])
{
cerr << "NoFormat und "<< refValues[exclusions[i]]<<" sind nicht zusammen erlaubt!" << endl;
exitArg = 1;
}
}
}
if(noRef == 1)
{
exitArg = 1;
}
if(exitArg != 1)
{
noRef = 1;
}
}
if(string(argv[i]) == "--parse-only")
{
vector<string> localExclusions = {"1", "2"};
for(int i = 0; i < exclusions.size(); i++)
{
for(int j = 0; j < localExclusions.size(); j++)
{
if(to_string(exclusions[i]) == localExclusions[j])
{
cerr << "parse-only und "<< refValues[exclusions[i]]<<" sind nicht zusammen erlaubt!" << endl;
exitArg = 1;
}
}
}
if(noRef == 1)
{
exitArg = 1;
}
if(exitArg != 1)
{
exclusions.push_back(3);
refValues[3] = "parse-only";noRef = 1;
}
if(i+1 != argc)
{
parseonlyStr = argv[i+1];
}
}
}
if(!outpathStr.empty() && outpathStr.length() > 1)
{
if((outpathStr.at(0) == '-' && outpathStr.at(1) == '-') || outpathStr.length() <= 1)
{
cout << "--out-path benötigt ein zusätzliches Argument!" << endl;
exitArg = 1;
}
}
if(!astylepathStr.empty() && astylepathStr.length() > 1)
{
if((astylepathStr.at(0) == '-' && astylepathStr.at(1) == '-') || astylepathStr.length() <= 1)
{
cout << "--astyle-path benötigt ein zusätzliches Argument!" << endl;
exitArg = 1;
}
}
if(!signperlineStr.empty() && signperlineStr.length() > 1)
{
if((signperlineStr.at(0) == '-' && signperlineStr.at(1) == '-') || signperlineStr.length() <= 1)
{
cout << "zu --sign-per-line wurde kein zusätzliches Argument übergeben, default-Wert: 79 wird übernommen!"<< endl;
}
}
if(!parseonlyStr.empty() && parseonlyStr.length() > 1)
{
if((parseonlyStr.at(0) == '-' && parseonlyStr.at(1) == '-') || parseonlyStr.length() <= 1)
{
cout << "--parse-only benötigt ein zusätzliches Argument!" << endl;
exitArg = 1;
}
}
try
{
signperlineInt = stol(signperlineParam);
}
catch (invalid_argument const &e)
{
cout << "Bad input: invalid_argument thrown for sign-per-line, using default Value if given" << endl;
}
catch (out_of_range const &e)
{
cout << "Integer overflow: out_of_range thrown for sign-per-line, using default Value if given" << endl;
}
if(exitArg > 0)
{
cout << "EXIT" << endl;
return;
}
for(int i = 1; i<argc; i++)
{
if(string(argv[i]) == "-h" || string(argv[i]) == "--help")
{
printHelp(signperlineInt);
continue;}
if(string(argv[i]) == "-v" || string(argv[i]) == "--version")
{
continue;}
if(string(argv[i]) == "--out-path")
{
cout << "Es wurde der Parameter --out-path erfolgreich übergeben!" << endl;
outpathBool = true;
cout << "Zusätzliche Argumente:" << outpathStr << endl;
outpathParam = outpathStr;
outpathBool = true;
continue;}
if(string(argv[i]) == "--astyle-path")
{
cout << "Es wurde der Parameter --astyle-path erfolgreich übergeben!" << endl;
astylepathBool = true;
cout << "Zusätzliche Argumente:" << astylepathStr << endl;
astylepathParam = astylepathStr;
astylepathBool = true;
continue;}
if(string(argv[i]) == "--sign-per-line")
{
cout << "Es wurde der Parameter --sign-per-line erfolgreich übergeben!" << endl;
signperlineBool = true;
cout << "Zusätzliche Argumente:" << signperlineStr << endl;
signperlineParam = signperlineStr;
signperlineBool = true;
continue;}
if(string(argv[i]) == "-n" || string(argv[i]) == "--only-if-newer")
{
cout << "Es wurde der Parameter --only-if-newer erfolgreich übergeben!" << endl;
onlyifnewerBool = true;
continue;}
if(string(argv[i]) == "--no-format")
{
cout << "Es wurde der Parameter --no-format erfolgreich übergeben!" << endl;
noformatBool = true;
continue;}
if(string(argv[i]) == "--parse-only")
{
ParseXML(parseonlyBool);
hallo(parseonlyBool);
continue;}
unknownOption(argv[i]);}
}
}
