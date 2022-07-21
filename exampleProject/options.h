#ifndef NEWFILE_H
#define NEWFILE_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;
namespace DHBW_Programmieren
{
class Beispiel_XML
{
bool isSetastylepathBool;
string astylepathParam;
bool isSetonlyifnewerBool;
bool isSetnoformatBool;
bool isSetoutpathBool;
string outpathParam;
bool parseonlyBool = 0;
bool isSetparseonlyBool;
string parseonlyParam;
int signperlineInt = 79;
bool isSetsignperlineBool;
string signperlineParam = "79";
int versionInt = 0;
bool isSetversionBool;
void myPrint(string myString, int newLineChecker);
bool isSetastylepath();
public:
string getValueOfastylepath();
public:
protected:
virtual void  printHelp(int signPerLine);
public:
bool isSetonlyifnewer();
public:
bool isSetnoformat();
public:
bool isSetoutpath();
public:
string getValueOfoutpath();
public:
bool isSetparseonly();
public:
bool getValueOfparseonly();
public:
bool isSetsignperline();
public:
int getValueOfsignperline();
public:
bool isSetversion();
public:
virtual void ParseXML(bool b) = 0;
public:
virtual void printVersion(int a) = 0;
public:
virtual void unknownOption(const string& unknown_option);void parseOptions(int argc, char* argv[]);
};
}
#endif