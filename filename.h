#ifndef FILENAME_H
#define FILENAME_H

#include <string>
#include <iostream>
#include <Vector>

using namespace std;
namespace parse
{
    class getOptsParse
    {
        bool boolVersion;
        bool boolOutputPath;
        string outpathParam;
        bool boolAstylePath;
        string astylepathParam;
        int signperlineInt;
        bool boolSignPerLine;
        string signperlineParam;
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
        
        int getValueOfSignPerLine();
        
        bool isSetn();
        
        bool isSetNoFormat();
        
        void parse(int argc, char* argv[]);
        
    };
}
#endif