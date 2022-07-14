#ifndef NEWFILE_H
#define NEWFILE_H
#include <string>
#include <iostream>
#include <Vector>
using namespace std;
namespace noNameSpace
{
    class noClassname
    {
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
    bool parseonlyBool = true;
    void myPrint(string myString, int newLineChecker);
    protected:
    virtual void  printHelp(int signPerLine);
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
    void ParseXML(bool parseonlyBool);
    public:
    void hallo(bool b);
    public:
    virtual void unknownOption(const string& unknown_option);void parse(int argc, char* argv[]);
    };
}
#endif
