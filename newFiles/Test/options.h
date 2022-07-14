#ifndef NEWFILE_H
#define NEWFILE_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;
namespace noNameSpace
{
class noClassname
{
bool boolIsSettest;
bool VersionBool;
bool outpathBool;
string outpathParam;
bool astylepathBool;
string astylepathParam;
int signperlineInt = 79;
bool signperlineBool;
string signperlineParam = "79";
bool onlyifnewerBool;
bool noformatBool;
int parseonlyInt = 0;
bool parseonlyBool;
string parseonlyParam;
void myPrint(string myString, int newLineChecker);
bool isSettest();
public:
bool isSetVersion();
public:
bool isSetoutpath();
public:
string getValueOfoutpath();
public:
bool isSetastylepath();
public:
string getValueOfastylepath();
public:
bool isSetsignperline();
public:
int getValueOfsignperline();
public:
bool isSetonlyifnewer();
public:
bool isSetnoformat();
public:
bool isSetparseonly();
public:
int getValueOfparseonly();
public:
void ParseXML(int parseonlyInt);
public:
virtual void unknownOption(const string& unknown_option);void parse(int argc, char* argv[]);
};
}
#endif