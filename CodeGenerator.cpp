#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;



class Code
{

    struct internalMethod
    {
        string methodName = "";
        string methodStart = "void" + methodName +"()\n{\n";
        string methodCode = "";
        string methodEnd = "}\n";
    };

    string imports = "#include <string>\n#include <iostream>\n#include <Vector>\nusing namespace std;\n";

    string variableDefinitions = "vector<int> exclusions;\n"                                                        //Vector mit allen bereits gesetzten Ref Nummern
                                 "int exitArg = 0;\n"                                                               //0 Alles ok, 1 Ungültige Argument Kombination
                                 "int noRef = -1;\n"                                                                //0 Keine Argumente mit einer Ref Nummer
                                 "";

    string returnIfWrongArgs = "if(exitArg > 0)\n{\ncout << \"EXIT\" << endl;\nreturn 0;\n}\n";

    string exclusionCheck;

    string pathRequiredCheck;

    string hasArgumentsCheck;

    string convertToInt;

    string code;

    string forLoopAllArgsStart = "for(int i = 1; i<argc; i++)\n{\n";
    string forLoopAllArgsClose = "}\n";

    string handleArgs = forLoopAllArgsStart;

    vector<string> intInitialise;
    vector<string> strInitialise;

    vector<internalMethod> internalMethods;

public:
    void createInt(string varName, int value)
    {
        string newLine = "int " + varName + " = " + to_string(value) + ";\n";
        code += newLine;
    }

    void setInt(string varName, int newValue)
    {
        code += varName + " = " + to_string(newValue) + " ;\n";
    }

    void createString(string varName, string value)
    {
        string newLine = "string " + varName + " = \"" + value + "\";\n";
        code += newLine;
    }

    void setString(string varName, string newValue)
    {
        code += varName + " = \"" + newValue + "\" ;\n";
    }

    void COUT(string message)
    {
       code += "cout << \"" + message + "\" << endl;\n";
    }

    void addText(string s)
    {
        code += s;
    }

    void addSingleComment(string s)
    {
        code += "//" + s;
    }

    void addMultiLineComment(string s)
    {
        code += "/*\n" + s + "\n*/\n";
    }

    string getCode()
    {
        return code;
    }

    void startForLoop(string s)
    {
        code += "for(" + s + ")\n{\n";
    }

    void endForLoop(){
        code += "}\n";
    }

    void startIf(string s)
    {
        code += "if(" + s + ")\n{\n";
    }

    void endIf()
    {
        code += "}\n";
    }

    string finalCode()
    {

        string s =  imports +
                    createInternalMethods() +
                    "int main(int argc, char* argv[])\n{\n" +
                    variableDefinitions +
                    forLoopAllArgsStart +
                    exclusionCheck +
                    forLoopAllArgsClose +
                    pathRequiredCheck +
                    convertToInt +
                    returnIfWrongArgs +
                    handleArgs +
                    "}\nreturn 0;\n}\n";
        return s;
    }

    string createInternalMethods()
    {
        Code methods = Code();

        for(int i = 0; i < internalMethods.size(); i++)
        {
            internalMethod iM = internalMethods[i];


            methods.addText("void " + iM.methodName + "()\n{\n");
            methods.addText(iM.methodCode);
            methods.addText(iM.methodEnd);
        }

        return methods.code;
    }

    void addArgument(string ref = "",
                     string shortOpt = "",
                     string longOpt = "",
                     string exclusion = "",                     //DONE
                     string connectToInternalMethod = "",
                     string description = "",
                     string interface = "",
                     string hasArguments = "",                  //DONE
                     string convertTo = "",
                     string defaultValue = ""                   //DONE
                                )                                                                          //Funktion, die alle Argumente aus der xml annimmt
    {

        string codeArgParse;
        string ifStateStart;
        string nameCheckBool;

        if(longOpt != "" && shortOpt != "")                                                                             //wenn longOpt und shortOpt gesetzt sind
        {
            nameCheckBool = "string(argv[i]) == \"--" + shortOpt + "\" || string(argv[i]) == \"--" + longOpt + "\"";
        }
        else if(longOpt != "")                                                                                          //Wenn nur longOpt gesetzt ist
        {
            nameCheckBool = "string(argv[i]) == \"--" + longOpt + "\"";
        }
        else if(shortOpt != "")                                                                                         //wenn nur shortOpt gesetzt ist
        {
            nameCheckBool = "string(argv[i]) == \"--" + shortOpt + "\"";
        }
//CODE
        ifStateStart = "if(" + nameCheckBool +")\n{";                                                                   //if-Statement String build

        if(exclusion != "")                                                                                             //Wenn Exclusions gesetzt sind
        {

            vector<int> exclusions;

            vector<string> exclusionStrings = split(exclusion, ',');

            Code exclCode = Code();

            string tempCode =  "vector<string> localExclusions = {";

            for(int i = 0; i < exclusionStrings.size(); i++)
            {
                tempCode += "\"" + exclusionStrings[i] + "\"";

                if(i+1 != exclusionStrings.size())
                {
                    tempCode += ", ";
                }
            }

            tempCode += "};\n";

            exclCode.addText(tempCode);

            exclCode.startForLoop("int i = 0; i < exclusions.size(); i++");
                exclCode.startForLoop("int j = 0; j < localExclusions.size(); j++");
                    exclCode.startIf("to_string(exclusions[i]) == localExclusions[j]");
                        exclCode.addText("cout << \"Es wurde eine ungültige Kombination von Argumenten angegeben!\" << endl;\n");
                        exclCode.addText("exitArg = 1;\n");
                    exclCode.endIf();
                exclCode.endForLoop();
            exclCode.endForLoop();

            exclCode.startIf("noRef == 0");
                exclCode.addText("cout << \"Es wurde ein Argument übergeben, dass Ref 1-3 nicht zulässt, --help ist somit verboten!\"<< endl;\n");
                exclCode.addText("exitArg = 1;\n");
            exclCode.endIf();

            exclCode.startIf("exitArg != 1");
            if(ref != "")
            {
                exclCode.addText("exclusions.push_back(" + ref + ");\n");
            }
                exclCode.addText("noRef = 1;\n");
            exclCode.endIf();

        exclusionCheck += ifStateStart;
            exclusionCheck += exclCode.getCode();

            if(hasArguments == "Required" || hasArguments == "optional")
            {
                exclusionCheck +="if(i+1 != argc)\n{\n" + interface + "Str = argv[i+1];\n}\n";
            }
        exclusionCheck += "}\n";



        }

        if(hasArguments == "Required")
        {
            Code pathCheckCode = Code();
            variableDefinitions += "string " + interface + "Str;\n";

            pathCheckCode.startIf("!" + interface + "Str.empty() && " + interface + "Str.length() > 1");
                pathCheckCode.startIf("(" + interface + "Str.at(0) == '-' && " + interface + "Str.at(1) == '-') || " + interface + "Str.length() <= 1");
                    pathCheckCode.addText("cout << \"--" + longOpt + " benötigt einen Pfad als Argument!\" << endl;\n");
                    pathCheckCode.addText("exitArg = 1;\n");
                pathCheckCode.endIf();
            pathCheckCode.endIf();

            pathCheckCode.startIf(interface +"Str.length() == 1");
                pathCheckCode.addText("cout << \"" +longOpt +" benötigt einen Pfad als Argument!\" << endl;\n");
                pathCheckCode.addText("exitArg = 1;\n");
            pathCheckCode.endIf();

            pathRequiredCheck += pathCheckCode.getCode();
        }

        if(defaultValue != "")
        {
            variableDefinitions += "string " + interface + "Str = \"" + defaultValue + "\";\n";
        }

        if(convertTo == "Integer")
        {
            string convertInt = "try\n{\nint " + interface + "Int = stol(" + interface + "Str);\n}\n";

            convertInt += "catch (invalid_argument const &e)\n{\n";
            convertInt += "cout << \"Bad input: invalid_argument thrown for " + longOpt + ", using default Value if given\" << endl;\n";
            convertInt += "exitArg = 1;\n}\n";

            convertInt += "catch (out_of_range const &e)\n{\n";
            convertInt += "cout << \"Integer overflow: out_of_range thrown for " + longOpt + ", using default Value if given\" << endl;\n";
            convertInt += "exitArg = 1;\n}\n";

            convertToInt += convertInt;
        }

        Code actOnArgs = Code();

        actOnArgs.startIf(nameCheckBool);
            if(connectToInternalMethod != "")
            {
                internalMethod iM = internalMethod();

                iM.methodName = connectToInternalMethod;
                iM.methodCode = "cout << \"" + description + "\" << endl;\n";
                //cout << "METHOD NAME IN I_M: " << iM.methodName << endl;

                internalMethods.push_back(iM);
                actOnArgs.addText(connectToInternalMethod + "();\n");
            }
            else
            {
                actOnArgs.addText("cout << \"Es wurde der Parameter --" + longOpt + " erfolgreich übergeben!\" << endl;\n");
                if(hasArguments != "")
                {
                    actOnArgs.addText("cout << \"Zusätzliche Argumente:\" << " + interface + "Str << endl;\n");
                }
            }
            actOnArgs.endIf();

            handleArgs += actOnArgs.code;


    }



    vector<string> split (string str, char seperator)
    {

        vector<string> subStrings;
        int currIndex = 0, i = 0;
        int startIndex = 0, endIndex = 0;
        while (i <= str.length())
        {
            if (str[i] == seperator || i == str.length())
            {
                endIndex = i;
                string subStr = "";
                subStr.append(str, startIndex, endIndex - startIndex);
                subStrings.push_back(subStr);
                currIndex += 1;
                startIndex = endIndex + 1;
            }
            i++;
        }
        return subStrings;
    }

};

int main() {
    /*
    std::cout << "Hello, World!" << std::endl;

    code.createInt("Anzahl", 5);
    code.createInt("testInt2", 7);
    code.COUT("Hallo Welt");
    code.createString("testStr", "Hallo");
    code.setInt("Anzahl", 3);
    code.setString("testStr", "Welt");
     */

    Code code = Code();

    code.startForLoop("int i = 1; i<argc; i++");

        code.addArgument("1", "h", "help", "2,3", "printHelp", "Diese Hilfe ausgeben und beenden", "", "", "", "");
        code.addArgument("2", "v", "version", "1,3", "printVersion", "Gibt die Version des Programms aus und beendet", "Version", "", "", "");
        code.addArgument("", "", "out-path", "1,2,3", "", "Der Pfad wo das Ergebnis hingenriert werden soll (sonst ins aktuelle Verzeichnis)", "OutputPath", "Required", "", "");
        code.addArgument("", "", "astyle-path", "1,2,3", "", "Der Pfad wo die Astyle executable gefunden werden kann", "AstylePath", "Required", "", "");
        code.addArgument("", "", "sign-per-line", "1,2,3", "", "Der Pfad wo die Astyle executable gefunden werden kann", "SignPerLine", "optional", "Integer", "79");
        code.addArgument("", "n", "only-if-newer", "1,2,3", "", "Generiert nur wenn die Eingangsdatei neuer ist wie die bereits generierte", "OnlyIfNewer", "", "", "");
        code.addArgument("", "", "no-format", "1,2,3", "", "Erzeugte Datei wird nicht formatiert", "NoFormat", "", "", "");
        code.addArgument("3", "", "parse-only", "1,2", "ParseXML", "Parst die Datei einmal und beendet das Programm", "", "", "", "");
    code.endForLoop();

    cout << "CODE: " << endl << code.finalCode();

    // Create and open a text file
    ofstream MyFile("filename.cpp");

    // Write to the file
    MyFile << code.finalCode();

    // Close the file
    MyFile.close();




    return 0;
}