#include <string>
#include <iostream>
#include <Vector>
using namespace std;
void printHelp()
{
    cout << "Diese Hilfe ausgeben und beenden" << endl;
}
void printVersion()
{
    cout << "Gibt die Version des Programms aus und beendet" << endl;
}
void ParseXML()
{
    cout << "Parst die Datei einmal und beendet das Programm" << endl;
}
int main(int argc, char* argv[])
{
    vector<int> exclusions;
    int exitArg = 0;
    int noRef = -1;
    string OutputPathStr;
    string AstylePathStr;
    string SignPerLineStr = "79";
    for(int i = 1; i<argc; i++)
    {
        if(string(argv[i]) == "--h" || string(argv[i]) == "--help")
        {vector<string> localExclusions = {"2", "3"};
            for(int i = 0; i < exclusions.size(); i++)
            {
                for(int j = 0; j < localExclusions.size(); j++)
                {
                    if(to_string(exclusions[i]) == localExclusions[j])
                    {
                        cout << "Es wurde eine ung├╝ltige Kombination von Argumenten angegeben!" << endl;
                        exitArg = 1;
                    }
                }
            }
            if(noRef == 0)
            {
                cout << "Es wurde ein Argument ├╝bergeben, dass Ref 1-3 nicht zul├ñsst, --help ist somit verboten!"<< endl;
                exitArg = 1;
            }
            if(exitArg != 1)
            {
                exclusions.push_back(1);
                noRef = 1;
            }
        }
        if(string(argv[i]) == "--v" || string(argv[i]) == "--version")
        {vector<string> localExclusions = {"1", "3"};
            for(int i = 0; i < exclusions.size(); i++)
            {
                for(int j = 0; j < localExclusions.size(); j++)
                {
                    if(to_string(exclusions[i]) == localExclusions[j])
                    {
                        cout << "Es wurde eine ung├╝ltige Kombination von Argumenten angegeben!" << endl;
                        exitArg = 1;
                    }
                }
            }
            if(noRef == 0)
            {
                cout << "Es wurde ein Argument ├╝bergeben, dass Ref 1-3 nicht zul├ñsst, --help ist somit verboten!"<< endl;
                exitArg = 1;
            }
            if(exitArg != 1)
            {
                exclusions.push_back(2);
                noRef = 1;
            }
        }
        if(string(argv[i]) == "--out-path")
        {vector<string> localExclusions = {"1", "2", "3"};
            for(int i = 0; i < exclusions.size(); i++)
            {
                for(int j = 0; j < localExclusions.size(); j++)
                {
                    if(to_string(exclusions[i]) == localExclusions[j])
                    {
                        cout << "Es wurde eine ung├╝ltige Kombination von Argumenten angegeben!" << endl;
                        exitArg = 1;
                    }
                }
            }
            if(noRef == 0)
            {
                cout << "Es wurde ein Argument ├╝bergeben, dass Ref 1-3 nicht zul├ñsst, --help ist somit verboten!"<< endl;
                exitArg = 1;
            }
            if(exitArg != 1)
            {
                exclusions.push_back();
                noRef = 1;
            }
            if(i+1 != argc)
            {
                OutputPathStr = argv[i+1];
            }
        }
        if(string(argv[i]) == "--astyle-path")
        {vector<string> localExclusions = {"1", "2", "3"};
            for(int i = 0; i < exclusions.size(); i++)
            {
                for(int j = 0; j < localExclusions.size(); j++)
                {
                    if(to_string(exclusions[i]) == localExclusions[j])
                    {
                        cout << "Es wurde eine ung├╝ltige Kombination von Argumenten angegeben!" << endl;
                        exitArg = 1;
                    }
                }
            }
            if(noRef == 0)
            {
                cout << "Es wurde ein Argument ├╝bergeben, dass Ref 1-3 nicht zul├ñsst, --help ist somit verboten!"<< endl;
                exitArg = 1;
            }
            if(exitArg != 1)
            {
                exclusions.push_back();
                noRef = 1;
            }
            if(i+1 != argc)
            {
                AstylePathStr = argv[i+1];
            }
        }
        if(string(argv[i]) == "--sign-per-line")
        {vector<string> localExclusions = {"1", "2", "3"};
            for(int i = 0; i < exclusions.size(); i++)
            {
                for(int j = 0; j < localExclusions.size(); j++)
                {
                    if(to_string(exclusions[i]) == localExclusions[j])
                    {
                        cout << "Es wurde eine ung├╝ltige Kombination von Argumenten angegeben!" << endl;
                        exitArg = 1;
                    }
                }
            }
            if(noRef == 0)
            {
                cout << "Es wurde ein Argument ├╝bergeben, dass Ref 1-3 nicht zul├ñsst, --help ist somit verboten!"<< endl;
                exitArg = 1;
            }
            if(exitArg != 1)
            {
                exclusions.push_back();
                noRef = 1;
            }
            if(i+1 != argc)
            {
                SignPerLineStr = argv[i+1];
            }
        }
        if(string(argv[i]) == "--n" || string(argv[i]) == "--only-if-newer")
        {vector<string> localExclusions = {"1", "2", "3"};
            for(int i = 0; i < exclusions.size(); i++)
            {
                for(int j = 0; j < localExclusions.size(); j++)
                {
                    if(to_string(exclusions[i]) == localExclusions[j])
                    {
                        cout << "Es wurde eine ung├╝ltige Kombination von Argumenten angegeben!" << endl;
                        exitArg = 1;
                    }
                }
            }
            if(noRef == 0)
            {
                cout << "Es wurde ein Argument ├╝bergeben, dass Ref 1-3 nicht zul├ñsst, --help ist somit verboten!"<< endl;
                exitArg = 1;
            }
            if(exitArg != 1)
            {
                exclusions.push_back();
                noRef = 1;
            }
        }
        if(string(argv[i]) == "--no-format")
        {vector<string> localExclusions = {"1", "2", "3"};
            for(int i = 0; i < exclusions.size(); i++)
            {
                for(int j = 0; j < localExclusions.size(); j++)
                {
                    if(to_string(exclusions[i]) == localExclusions[j])
                    {
                        cout << "Es wurde eine ung├╝ltige Kombination von Argumenten angegeben!" << endl;
                        exitArg = 1;
                    }
                }
            }
            if(noRef == 0)
            {
                cout << "Es wurde ein Argument ├╝bergeben, dass Ref 1-3 nicht zul├ñsst, --help ist somit verboten!"<< endl;
                exitArg = 1;
            }
            if(exitArg != 1)
            {
                exclusions.push_back();
                noRef = 1;
            }
        }
        if(string(argv[i]) == "--parse-only")
        {vector<string> localExclusions = {"1", "2"};
            for(int i = 0; i < exclusions.size(); i++)
            {
                for(int j = 0; j < localExclusions.size(); j++)
                {
                    if(to_string(exclusions[i]) == localExclusions[j])
                    {
                        cout << "Es wurde eine ung├╝ltige Kombination von Argumenten angegeben!" << endl;
                        exitArg = 1;
                    }
                }
            }
            if(noRef == 0)
            {
                cout << "Es wurde ein Argument ├╝bergeben, dass Ref 1-3 nicht zul├ñsst, --help ist somit verboten!"<< endl;
                exitArg = 1;
            }
            if(exitArg != 1)
            {
                exclusions.push_back(3);
                noRef = 1;
            }
        }
    }
    if(!OutputPathStr.empty() && OutputPathStr.length() > 1)
    {
        if((OutputPathStr.at(0) == '-' && OutputPathStr.at(1) == '-') || OutputPathStr.length() <= 1)
        {
            cout << "--out-path ben├Âtigt einen Pfad als Argument!" << endl;
            exitArg = 1;
        }
    }
    if(OutputPathStr.length() == 1)
    {
        cout << "out-path ben├Âtigt einen Pfad als Argument!" << endl;
        exitArg = 1;
    }
    if(!AstylePathStr.empty() && AstylePathStr.length() > 1)
    {
        if((AstylePathStr.at(0) == '-' && AstylePathStr.at(1) == '-') || AstylePathStr.length() <= 1)
        {
            cout << "--astyle-path ben├Âtigt einen Pfad als Argument!" << endl;
            exitArg = 1;
        }
    }
    if(AstylePathStr.length() == 1)
    {
        cout << "astyle-path ben├Âtigt einen Pfad als Argument!" << endl;
        exitArg = 1;
    }
    try
    {
        int SignPerLineInt = stol(SignPerLineStr);
    }
    catch (invalid_argument const &e)
    {
        cout << "Bad input: invalid_argument thrown for sign-per-line, using default Value if given" << endl;
        exitArg = 1;
    }
    catch (out_of_range const &e)
    {
        cout << "Integer overflow: out_of_range thrown for sign-per-line, using default Value if given" << endl;
        exitArg = 1;
    }
    if(exitArg > 0)
    {
        cout << "EXIT" << endl;
        return 0;
    }
    for(int i = 1; i<argc; i++)
    {
        if(string(argv[i]) == "--h" || string(argv[i]) == "--help")
        {
            printHelp();
        }
        if(string(argv[i]) == "--v" || string(argv[i]) == "--version")
        {
            printVersion();
        }
        if(string(argv[i]) == "--out-path")
        {
            cout << "Es wurde der Parameter --out-path erfolgreich ├╝bergeben!" << endl;
            cout << "Zus├ñtzliche Argumente:" << OutputPathStr << endl;
        }
        if(string(argv[i]) == "--astyle-path")
        {
            cout << "Es wurde der Parameter --astyle-path erfolgreich ├╝bergeben!" << endl;
            cout << "Zus├ñtzliche Argumente:" << AstylePathStr << endl;
        }
        if(string(argv[i]) == "--sign-per-line")
        {
            cout << "Es wurde der Parameter --sign-per-line erfolgreich ├╝bergeben!" << endl;
            cout << "Zus├ñtzliche Argumente:" << SignPerLineStr << endl;
        }
        if(string(argv[i]) == "--n" || string(argv[i]) == "--only-if-newer")
        {
            cout << "Es wurde der Parameter --only-if-newer erfolgreich ├╝bergeben!" << endl;
        }
        if(string(argv[i]) == "--no-format")
        {
            cout << "Es wurde der Parameter --no-format erfolgreich ├╝bergeben!" << endl;
        }
        if(string(argv[i]) == "--parse-only")
        {
            ParseXML();
        }
    }
    return 0;
}
