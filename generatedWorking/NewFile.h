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
        bool boolVersion;
        bool boolOutputPath;
        string outpathParam;
        bool boolAstylePath;
        string astylepathParam;
        int signperlineInt = 79;
        bool boolSignPerLine;
        string signperlineParam = "79";
        bool boolOnlyIfNewer;
        bool boolNoFormat;
        void myPrint(string myString, int newLineChecker);
        protected: virtual void printHelp(int signPerLine);
        public:
        bool isSetversion();
        bool isSetOutputPath();
        string getValueOfOutputPath();
        bool isSetAstylePath();
        string getValueOfAstylePath();
        bool isSetSignPerLine();
        int getValueOfsignperline();
        bool isSetn();
        bool isSetNoFormat();
        virtual void unknownOption(const string& unknown_option);
        void parse(int argc, char* argv[]);
    };
}
#endif