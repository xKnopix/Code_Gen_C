// Autor: Jacob Hochbaum

#include "../headerFiles/CodeGenerator.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

/*
 * Diese Klasse soll dazu dienen, einfacher und uebersichtlicher
 * ein Programm zu schreiben, welches als output c++ Code hat
 *
 *
 *
 *
 *
 *
 */

// Deklaration aller Strings, die benoetigt werden, um den c++ Code zu generieren
////handleArgs////
// In handleArgs wird eine 2. For-Schliefe gespeichert, welche nach dem
// die Argumente auf ihre Korrektheit ueberprueft wurden nochmals alle Argumente
// durch-iteriert und nun auf die uebergebenen Argumente reagiert.

Code::Code()
{
}

Code::Code(string sourceFileName, string headerFileName, string nameSpace, string className, string signPerLine,
           string sampleUsage, string author)
{

    Code::headerFileName = headerFileName;
    Code::nameSpace = nameSpace;
    Code::className = className;
    Code::signPerLine = signPerLine;
    Code::sampleUsage = sampleUsage;
    Code::author = author;
}

void Code::addText(string s)
{

    code += s;
}

string Code::getCode()
{
    /*
     *Der generierte Code-String wird zurueckgegeben
     */

    return code;
}

void Code::startForLoop(string s)
{

    code += "for(" + s + ")\n{\n";
}

void Code::endForLoop()
{
    /*
     * NUR Fuer lesbarkeit!
     * Es wird eine geschweifte Klammer angehaengt, um eine begonnene for-Schleife zu schließen
     */
    code += "}\n";
}

void Code::startIf(string s)
{
    /*
     * Es wird Code generiert, um eine if-Verzweigung im gesamt Code zu starten
     */
    ///:param s: die Bedingung der if-Verzweigung als String (!Muss Stimmen!)
    code += "if(" + s + ")\n{\n";
}

void Code::endIf()
{
    /*
     * NUR FueR LESBARKEIT!
     * Es wird eine geschweifte Klammer angehaengt, um eine begonnene Verzweigung zu schließen
     */
    code += "}\n";
}

string Code::capitalizeString(string s)
{
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c)
              { return toupper(c); });
    return s;
}

string Code::finalHeaderCode(xml_parser::GetOptSetup data)
{
    string defString = Code::capitalizeString(headerFileName);

    for (int i = 0; i < 2; i++)
    {
        defString.pop_back();
    }

    defString += "_H";

    string methodNames = "private: void myPrint(string myString, int newLineChecker);\n";

    // Es wird ein String erstellt, um alle Methoden zu definieren
    for (int i = 0; i < internalMethods.size(); i++)
    {

        internalMethod iM = internalMethods[i];

        if (iM.methodName == "printHelp")
        {
            iM.expectedVars = "const int signPerLine";
            iM.privacy = "protected:";
            iM.returnType = "\nvirtual void ";
        }

        methodNames += iM.privacy + iM.returnType + " " + iM.methodName + "(" + iM.expectedVars + ");\n\n";
    }

    for (int i = 0; i < externalMethods.size(); i++)
    {
        externalMethod eM = externalMethods[i];

        methodNames += eM.privacy + eM.returnType + " " + eM.methodName + "(" + eM.expectedVars + ") = 0;\n\n";
    }

    // std::cout << methodNames << endl;

    return "#ifndef " + defString + "\n"
                                    "#define " + // Include-Guard
           defString +
           "\n" +
           includesString +                               // alle Includes
           namespaceString +                              // using namespace std
           "namespace " + data.nameSpace.content + "\n" + // der eigene Namespace der Klasse
           "{\n" +
           "class " + data.className.content + "\n" + // die Klasse wird definiert
           "{\n" +
           globalVariables +                                             // die globalen Variablen der Klasse werden definiert
           methodNames +                                                 // die Methoden deklarationen
           "virtual void unknownOption(const string& unknown_option);" + // die unknownOption - Methode
           "\n public: void parseOptions(int argc, char* argv[]);\n" +   // die parseOptions Methode
           "};\n"
           "}\n"
           "#endif"; // include-Guard Ende
}

string Code::finalCode(xml_parser::GetOptSetup data)
{
    /*
     * Der Finale Code wird erstellt und zurueckgegeben
     * Es werden hierfuer alle entstandenen zwischen Strings zusammengefuegt und zurueckgegeben
     */
    ///:return: den gesamt Code {string}

    // std::cout << "Finmal: " << hFileName << endl;

    if (data.nameSpace.content.empty())
    {
        return includesString +
               "#include \"" + data.headerFileName.content + "\"\n" + // das generierte h-file wird includiert
               namespaceString +
               /* globalVariables + */
               createInternalMethods(data) +                                                      // die Methoden werden definiert
               "void " + data.className.content + "::unknownOption(const string& unknown_option)" // die unknownOption - Methode wird definiert
                                                  "\n{\n\tcout << \"Unbekannter Parameter '\" + unknown_option + \"'!\" << endl;\nexit(EXIT_SUCCESS);\n}\n" +

               "void " + data.className.content + "::parseOptions(int argc, char* argv[])\n" // die parseOptions - Methode wird definiert
                                                  "{\n" +
               variableDefinitions + // alle variablen innerhalb der parseOptions - Methode

               forLoopAllArgsStart + // Generierung der forschleife, um alle argumente aus argv durchzugehen
               exclusionCheck +      // Code generierung, um exclusions zu pruefen
               forLoopAllArgsClose + // Die Generierung der For-Schleife wird abgeschlossen

               pathRequiredCheck + // Code generierung um zu pruefen, ob ein zusaetzliches Argument uebergeben wurde, oder ob wieder ein neues Argument mit '-' beginnend folgt
               convertToInt +      // Code Generierung, um die Wandlung zu einem Integer durchzufuehren
               returnIfWrongArgs + // Code Generierung: Wenn Exclusions angeschlagen sind soll das Programm beendet werden
               handleArgs +        // Code Generierung: Es folgt eine 2. Forschleife, wenn keine Exclusions aufgetreten sind und die Argumente werden "normal" geparst
               "int temp = 0;" +
               "for(int m = 0; m < additionalParams.size(); m++)" // Code Generierung: Es werden alle zusaetzlichen Argumente in einem Vector gespeichert, ueber den dann herausgefunden werden kann, ob ein unbekanntes Argument vorkommt
               "{"
               "   if(additionalParams[m] == argv[i])\n{\ntemp = 1;\n}\n"
               "}" +
               "if(temp == 1)\n{continue;\n}\n" +
               unknownOptionMethodCall + // der Aufruf für die unknownOption - Methode wird generiert
               "}\n"
               "}\n";
    }
    else
    {
        // Der code wird ohne namespace generiert, wie oben, wenn kein namespace angegeben wurde
        return includesString +
               "#include \"" + data.headerFileName.content + "\"\n" +
               namespaceString +
               "namespace " + data.nameSpace.content + "\n" +
               "{\n" +
               /*globalVariables + */
               createInternalMethods(data) +
               "void " + data.className.content + "::unknownOption(const string& unknown_option)"
                                                  "\n{\n\tcout << \"Unbekannter Parameter '\" + unknown_option + \"'!\" << endl;\nexit(EXIT_SUCCESS);\n}\n" +

               "void " + data.className.content + "::parseOptions(int argc, char* argv[])\n"
                                                  "{\n" +
               variableDefinitions +

               forLoopAllArgsStart +
               exclusionCheck +
               forLoopAllArgsClose +

               pathRequiredCheck +
               convertToInt +
               returnIfWrongArgs +
               handleArgs +
               "int temp = 0;" +
               "for(int m = 0; m < additionalParams.size(); m++)"
               "{"
               "   if(additionalParams[m] == argv[i])\n{\ntemp = 1;\n}\n"
               "}" +
               "if(temp == 1)\n{continue;\n}\n" +
               unknownOptionMethodCall +
               "}\n"
               "}\n"
               "}\n";
    }
}

string Code::createInternalMethods(xml_parser::GetOptSetup data)
{
    /*
     * Der Vektor mit allen Instanzen des Structs internalMethod wird durch-iteriert
     * und die Implementierung der Methoden erstellt
     * Alle Implementierungen werden in einem gesamt String gespeichert und zurueckgegeben
     */

    ///:return: die Implementierung aller Methoden {string}

    Code methods = Code();

    string methodNames;

    ///////////////////////myPrint fuer signPerLine erstellen

    internalMethod myPrint = internalMethod();
    myPrint.methodName = data.className.content + "::myPrint";
    myPrint.methodCode =
        "int lineLength = newLineChecker;\n"
        "for (auto i = 0; i != myString.size(); ++i)\n"
        "{\n"
        "if (i == newLineChecker)\n"
        "{\n"
        "newLineChecker += lineLength;\n"
        "cout << endl;\n"
        "}\n"

        "cout << myString[i];\n"
        "}\n";

    methods.addText("void " + myPrint.methodName + "(string myString, int newLineChecker)\n{\n");
    methods.addText(myPrint.methodCode);
    methods.addText(myPrint.methodEnd);

    for (int i = 0; i < internalMethods.size(); i++)
    {

        internalMethod iM = internalMethods[i];

        // std::cout << "building Method: " << iM.methodName << endl;

        if (iM.methodName ==
            "printHelp") // HelpMethode wird erstellt
        {
            iM.expectedVars = "const int signPerLine";
            iM.methodName = data.className.content + "::" + iM.methodName;
            if (!authorCodeAdded)
            {
                printHelpMethodCode += "myPrint(\"\\n\", " + data.signPerLine + ");\n";
                printHelpMethodCode += "myPrint(\"Sample Usage:\\n\", " + data.signPerLine + ");\n";
                for (int ij = 0; ij < data.sampleUsage.sample.size(); ij++)
                {
                    printHelpMethodCode += "myPrint(\"" + data.sampleUsage.sample[ij].content + "\\n\", " + data.signPerLine + ");\n";
                }
                printHelpMethodCode += "myPrint(\"\\n\", " + data.signPerLine + ");\n";
                printHelpMethodCode += "myPrint(\"Overall-Description:\\n\", " + data.signPerLine + ");\n";
                for (int ij = 0; ij < data.overAllDescription.block.size(); ij++)
                {
                    printHelpMethodCode += "myPrint(\"" + data.overAllDescription.block[ij].content + "\\n\", " + data.signPerLine + ");\n";
                }
                printHelpMethodCode += "myPrint(\"\\n\", " + data.signPerLine + ");";
                printHelpMethodCode += "myPrint(\"Author Name: " + data.author.name + ", \", " + data.signPerLine + ");\n";
                printHelpMethodCode += "myPrint(\"Author Mail: " + data.author.mail + ", \", " + data.signPerLine + ");\n";
                printHelpMethodCode += "myPrint(\"Author Phone: " + data.author.phone + "\\n\", " + data.signPerLine + ");\n";
                authorCodeAdded = true;
            }

            iM.methodCode = "cout<<\"" + sampleUsage + "\"<< endl;\n" + printHelpMethodCode;

            methods.addText("void " + iM.methodName + "(const int signPerLine)\n{\n");
            methods.addText(iM.methodCode);
            methods.addText(iM.methodEnd);
            // methods.addText("\npublic:\n");

            methodNames += iM.methodName + "();\n";
        }
        else
        {
            methods.addText(iM.returnType + " " + data.className.content + "::" + iM.methodName + "(" + iM.expectedVars + ")\n{\n");
            methods.addText(iM.methodCode);
            methods.addText(iM.methodEnd);

            methodNames += iM.methodName +
                           "();\n";
        }
    }

    return methods.code;
}

vector<string> Code::split(string str, char seperator)
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

void Code::parse(xml_parser::GetOptSetup data)
{

    string sampleUsage;
    string overAllDescription;

    for (int i = 0; i < data.sampleUsage.sample.size(); i++)
    {
        sampleUsage += data.sampleUsage.sample[i].content + "\n";
    }

    data.overAllDescription.block[0];
    Code(data.sourceFileName.content, data.headerFileName.content, data.nameSpace.content, data.className.content, data.signPerLine, sampleUsage, data.author.name);

    startForLoop("int i = 1; i<argc; i++");

    for (int i = 0; i < data.options.option.size(); i++)
    {
        addArgument(data.options.option[i].ref,
                    data.options.option[i].shortOpt,
                    data.options.option[i].longOpt,
                    data.options.option[i].exclusion,
                    data.options.option[i].connectToInternalMethod,
                    data.options.option[i].description,
                    data.options.option[i].interface,
                    data.options.option[i].hasArguments,
                    data.options.option[i].convertTo,
                    data.options.option[i].defaultValue,
                    data.options.option[i].connectToExternalMethod,
                    data.signPerLine);
    }

    endForLoop(); // For Schleife fertig, der  rest kommt in finalCode()

    // Eine Datei öffnen
    ofstream MyFile(data.sourceFileName.content);

    // In die Datei reinschreiben
    MyFile
        << finalCode(data); // Code in Datei schreiben

    // Die Datei wieder schließen
    MyFile.close();

    ofstream MyHeaderFile(data.headerFileName.content);

    MyHeaderFile
        << finalHeaderCode(data);

    MyHeaderFile.close();
}

void Code::addArgument(const string ref,
                       const string shortOpt,
                       const string longOpt,
                       const string exclusion, // DONE
                       const string connectToInternalMethod,
                       const string description,
                       const string interface,
                       const string hasArguments, // DONE
                       const string convertTo,
                       const string defaultValue, // DONE
                       const string connectToExternalMethod,
                       const string GetOptSetupsignPerLineDefaultValue) // Funktion, die alle Argumente aus der xml annimmt
{
    if (headerFileName.empty())
    {
        std::cerr << "Es muss ein Name fuer die Header-Datei in der XML-Datei angegeben werden!" << endl;
        exit(EXIT_SUCCESS);
    }

    if (sourceFileName.empty())
    {
        std::cerr << "Es muss ein Name fuer die Source-Code-Datei in der XML-Datei angegeben werden!" << endl;
        exit(EXIT_SUCCESS);
    }

    string reference;
    size_t found = longOpt.find('-');
    if (found != string::npos)
    {
        reference = longOpt;
        reference.erase(remove(reference.begin(), reference.end(), '-'), reference.end()); // remove A from string
    }
    else if (interface != "")
    {
        reference = interface;
    }
    else if (longOpt != "")
    {
        reference = longOpt;
    }
    else if (shortOpt != "")
    {
        reference = shortOpt;
    }
    if (reference == "")
    {
        cerr
            << "Fehler beim Parsen der xml-Datei, etwas scheint mit shortOpt, longOpt und interface nicht in Ordnung zu sein! bei: "
            << longOpt << endl;
    }

    // std::cout << "REFERENZ = " << reference << endl;

    // string codeArgParse;
    string ifStateStart;
    string nameCheckBool;

    boolIsSetName = reference + "Bool"; ////Generierung des bool-Strings
    if (longOpt != "" && shortOpt !=
                             "") // wenn longOpt und shortOpt gesetzt sind
    {
        nameCheckBool = "string(argv[i]) == \"-" + shortOpt + "\" || string(argv[i]) == \"--" + longOpt + "\"";
    }
    else if (longOpt !=
             "") // Wenn nur longOpt gesetzt ist
    {
        nameCheckBool = "string(argv[i]) == \"--" + longOpt + "\"";
    }
    else if (shortOpt !=
             "") // wenn nur shortOpt gesetzt ist
    {
        nameCheckBool = "string(argv[i]) == \"-" + shortOpt + "\"";
    }
    ///////////////////////////////////////////////////

    ifStateStart = "if(" + nameCheckBool +
                   ")\n{\n"; // if-Statement String build

    if (exclusion !=
        "") ////exclusions////
    {

        vector<int> exclusions; ////exclusions////
        // exclusions werden in dem Format "1,2,3,4,..." uebergeben
        // dieser String wird jeweils an einem Komma getrennt und die einzelnen Elemente
        // in dem Vector exclusions als Integer gespeichert

        vector<string> exclusionStrings = split(exclusion,
                                                ','); // Der String wird aufgetrennt

        Code exclCode = Code(); // Es wird eine instanz der Klasse Code erzeugt, um den zu generierenden Code
        // lesbarer, bzw. uebersichtlicher erstellen zu koennen

        string tempCode = "vector<string> localExclusions = {"; ////tempCode////
        // wird benutzt, um Code zu generieren, welcher
        // einen string-Vektor erstellt, mit allen Exclusions, die bei dem Argument,
        // welches gerade "erstellt" wird, gesetzt sind

        for (int i = 0; i < exclusionStrings.size(); i++)
        {
            tempCode += "\"" + exclusionStrings[i] + "\"";

            if (i + 1 != exclusionStrings.size())
            {
                tempCode += ", ";
            }
        }

        tempCode += "};\n";

        // Die Exclusions wurden ueberprueft

        tempCode += "for (int m = 0; m < localExclusions.size(); m++)";
        tempCode += "\n{";

        tempCode += "for(int k = 0; k < refValuesSorted.size(); k++)";
        tempCode += "\n{";

        tempCode += "if(refValuesSorted[k] == localExclusions[m])";
        tempCode += "\n{";

        tempCode += "cout << \"--" + reference + " ist nicht erlaubt mit \" + argumentnames[k] << endl;";
        tempCode += "\nexit(EXIT_FAILURE);";

        tempCode += "\n}\n}\n}";

        tempCode += "exclusionValuesSorted.push_back(localExclusions);\n";

        tempCode += "argumentnames.push_back(\"--" + reference + "\");\n"; // hier loeschen

        if (ref != "")
        {
            // Wenn eine referenz nummer existiert müssen exclusions geprüft werden, Code Generierung dafür hier:
            tempCode += "for (int j = 0; j < exclusionValuesSorted.size(); j++)";
            tempCode += "\n{";
            tempCode += "vector<string> tempExclusionVec = exclusionValuesSorted[j];";
            tempCode += "for (int k = 0; k < tempExclusionVec.size(); k++)";
            tempCode += "\n{";
            tempCode += "if (\" " + ref + "\" == tempExclusionVec[k])";
            tempCode += "\n{";
            tempCode += "cout << \"--" + reference + " ist nicht erlaubt mit \" + argumentnames[j] << endl;";
            tempCode += "\nexit(EXIT_FAILURE);";
            tempCode += "\n}\n}\n}";
            tempCode += "vector<string> temp = {\"" + ref + "\"};\n";
            tempCode += "refValuesSorted.push_back(to_string(" + ref + "));\n";
        }
        else
        {
            tempCode += "refValuesSorted.push_back(\"x\");\n";
        }
        // Code zur Vektor-Generierung ist erstellt

        if (hasArguments == "")
        {
            tempCode += "\n}";
        }
        exclCode.addText(tempCode); // Code wird in in den Code zur Exclusion-ueberpruefung eingefuegt

        exclusionCheck += ifStateStart;
        exclusionCheck += exclCode.getCode();

        if (hasArguments == "Required" || hasArguments == "optional")
        {
            // Code Generierung um zu prüfen, ob zusätzliche Argumente angegeben wurden
            exclusionCheck += "if(i+1 < argc)\n{\n" + reference +
                              "Str = argv[i+1];\n}\n"; // Code Generierung um zusaetzliche Argumente einzulesen, falls diese Moeglich sein sollen
            if (hasArguments == "Required")
            {
                exclusionCheck += "else\n{";
                exclusionCheck += "cout << \"--" + longOpt + " benoetigt ein zusaetzliches Argument!\\n\"\n\"\" << endl;\nexit(EXIT_FAILURE);\n\n";
                exclusionCheck += "cerr << \"ERROR: --" + longOpt + " benoetigt ein zusaetzliches Argument!\\n\"\n\"\" << endl;\nexit(EXIT_FAILURE);\n}\n";
            }

            exclusionCheck += "additionalParams.push_back(" + reference + "Str);\n";
            exclusionCheck += "}\n";
        }
    }
    if (ref != "" && exclusion == "")
    {
        // Code Generierung für den Fall, dass es eine Referenznummer gibt, aber keine Exclusions in der Option
        exclusionCheck += "if(" + nameCheckBool + ")";
        exclusionCheck += "\n{";
        exclusionCheck += "for(int r = 0; r < exclusionValuesSorted.size(); r++)";
        exclusionCheck += "\n{";
        exclusionCheck += "vector<string> temp = exclusionValuesSorted[r];\n";

        exclusionCheck += "for(int q = 0; q < temp.size(); q++)";
        exclusionCheck += "{\n";

        exclusionCheck += "if(to_string(" + ref + ") == temp[q])";
        exclusionCheck += "\n{";
        exclusionCheck += "cout << \"--" + reference + " ist nicht erlaubt mit \" + argumentnames[r] << endl;";
        exclusionCheck += "exit(EXIT_FAILURE);";
        exclusionCheck += "\n}";

        exclusionCheck += "}\n";

        exclusionCheck += "\n}\n";
        exclusionCheck += "vector<string> tempVec = {\"x\"};\n";
        exclusionCheck += "refValuesSorted.push_back(to_string(" + ref + "));\n";
        exclusionCheck += "exclusionValuesSorted.push_back(tempVec);\n";

        exclusionCheck += "argumentnames.push_back(\"--" + reference + "\");\n";
        exclusionCheck += "\n}";
    }

    if (hasArguments ==
        "Required") // Code Generierung, um zu ueberpruefen, ob ein zusaetzliches Argument angegeben wurde,
    // wenn es required ist
    {
        Code pathCheckCode = Code(); // pathCheckCode//
        // Neue Instanz von Code() um zu generierenden Code zwischenzuspeichern

        variableDefinitions += "string " + reference + "Str;\n";

        pathCheckCode.startIf("!" + reference + "Str.empty() && " + reference + "Str.length() > 1");
        pathCheckCode.startIf(
            "(" + reference + "Str.at(0) == '-') || " + reference +
            "Str.length() <= 1");
        pathCheckCode.addText("cout << \"--" + longOpt + " benoetigt ein zusaetzliches Argument!\\n Da der naechste Parameter mit einem '-' startet, oder zu kurz (<1) ist, wurde kein zusaetzliches Argument erkannt!\"\n\"\" << endl;\n");
        pathCheckCode.addText("cerr << \"ERROR: --" + longOpt + " benoetigt ein zusaetzliches Argument!\\n Da der naechste Parameter mit einem '-' startet, oder zu kurz (<1) ist, wurde kein zusaetzliches Argument erkannt!\"\n\"\" << endl;\n");
        pathCheckCode.addText("exit(EXIT_FAILURE);\n");
        pathCheckCode.endIf();
        pathCheckCode.endIf();

        /*pathCheckCode.startIf(reference +"Str.length() == 1");
            pathCheckCode.addText("cout << \"" +longOpt +" benoetigt ein zusaetzliches Argument!\" << endl;\n");
            pathCheckCode.addText("exitArg = 1;\n");
        pathCheckCode.endIf(); */

        pathRequiredCheck += pathCheckCode.getCode();
    }

    if (hasArguments ==
        "optional") // Code Generierung, um zu ueberpruefen, ob ein zusaetzliches Argument angegeben wurde,
    // wenn es required ist
    {
        Code pathCheckCode = Code(); // pathCheckCode//
        // Neue Instanz von Code() um zu generierenden Code zwischenzuspeichern

        if (defaultValue == "")
        {
            variableDefinitions += "string " + reference + "Str;\n";
        }

        if (!defaultValue.empty()) // Code Generierung, falls es default Parameter gibt
        {
            variableDefinitions += "string " + reference + "Str = \"" + defaultValue + "\";\n";
        }

        pathCheckCode.startIf("!" + reference + "Str.empty() && " + reference + "Str.length() > 1");
        pathCheckCode.startIf(
            "(" + reference + "Str.at(0) == '-' && " + reference + "Str.at(1) == '-') || " + reference +
            "Str.length() <= 1");
        pathCheckCode.addText(
            "cout << \"zu --" + longOpt + " wurde kein zusaetzliches Argument uebergeben, default-Wert: " +
            defaultValue + " wird uebernommen!\"<< endl;\n");
        pathCheckCode.endIf();
        pathCheckCode.endIf();

        pathRequiredCheck += pathCheckCode.getCode();
    }

    // Code Generierung fuer convertToInt mit try-catch
    if (convertTo == "Integer" || convertTo == "integer")
    {

        if (defaultValue != "")
        {
            globalVariables += "int " + reference + "Int = " + defaultValue + ";\n";
            additionalParamVarName = interface + "Int";
            string convertInt = "try\n{\n" + reference + "Int = stol(" + reference + "Param);\n}\n";
            additionalParamVarName = reference + "Int";

            convertInt += "catch (invalid_argument const &e)\n{\n";
            convertInt += "cout << \"Bad input: invalid_argument thrown for " + longOpt +
                          ", using default Value if given\" << endl;\n";
            convertInt += "cerr << \"Bad input: invalid_argument thrown for " + longOpt +
                          ", using default Value if given\" << endl;\n";
            convertInt += "}\n";

            convertInt += "catch (out_of_range const &e)\n{\n";
            convertInt += "cout << \"Integer overflow: out_of_range thrown for " + longOpt +
                          ", using default Value if given\" << endl;\n";
            convertInt += "cerr << \"Integer overflow: out_of_range thrown for " + longOpt +
                          ", using default Value if given\" << endl;\n";
            convertInt += "}\n";

            convertToInt += convertInt;
        }
        else
        {
            globalVariables += "int " + reference + "Int = 0;\n";
            additionalParamVarName = interface + "Int";
        }
    }

    if (convertTo == "Bool" || convertTo == "bool")
    // Code Generierung für die ConvertToBool - Abhandlung
    {
        if (defaultValue != "")
        {
            globalVariables += "bool " + reference + "Bool = " + defaultValue + ";\n";
            additionalParamVarName = reference + "Bool";
        }
        else
        {
            globalVariables += "bool " + reference + "Bool = 0;\n";
            additionalParamVarName = reference + "Bool";
        }

        string convertBool = "try\n{\n" + reference + "Bool = " + reference + "Param;\n}\n";
        additionalParamVarName = reference + "Bool";

        convertBool += "catch (exception &e)\n{\n";
        convertBool += "cout << \"Parameter bool von " + longOpt +
                       "konnte nicht konvertiert werden, using default Value if given\" << endl;\n";
        convertBool += "}\n";
    }

    // zum gesamt Code hinzufuegen

    if (!shortOpt.empty() && !longOpt.empty())
    {
        printHelpMethodCode += "myPrint(\"-" + shortOpt + ", --" + longOpt + "\\n\", " + GetOptSetupsignPerLineDefaultValue + ");\n";
    } // Die Description wird an einen globalen string hinzugefuegt fuer die printHelp Methode

    if (shortOpt.empty() && !longOpt.empty())
    {
        printHelpMethodCode += "myPrint(\"--" + longOpt + "\\n\", " + GetOptSetupsignPerLineDefaultValue + ");\n";
    }

    if (!shortOpt.empty() && longOpt.empty())
    {
        printHelpMethodCode += "myPrint(\"-" + shortOpt + "\\n\",  " + GetOptSetupsignPerLineDefaultValue + ");\n";
    }

    printHelpMethodCode += "myPrint(\"  " + description + "\\n\\n\", " + GetOptSetupsignPerLineDefaultValue + ");\n";

    if (!interface.empty())
    {

        globalVariables += "bool isSet" + reference + "Bool;\n";

        internalMethod iM;

        iM.methodName = "isSet" + reference;

        iM.methodCode = "return isSet" + reference + "Bool;\n";
        iM.privacy = "public: ";
        iM.returnType = "bool";

        internalMethods.push_back(iM);

        if (hasArguments != "")
        {
            // Code Generierung, wenn hasArguments gesetzt ist.
            if (hasArguments == "Required")
            {
                globalVariables += "string " + reference + "Param;\n";
                additionalParamVarName = reference + "Param";
            }

            if (hasArguments == "optional")
            {
                globalVariables += "string " + reference + "Param = \"" + defaultValue + "\";\n";
                additionalParamVarName = reference + "Param";
            }

            // Es folgt die Code - Generierung für die Bool und Integer Konvertierung
            if (convertTo == "Integer" || convertTo == "integer")
            {
                additionalParamVarName = reference + "Int";
                internalMethod iM;
                iM.privacy = "public: ";
                iM.returnType = "int";

                iM.methodCode = "try {\n"
                                "                " +
                                reference + "Int = stol(" + reference + "Param);\n"
                                                                        "            }\n"
                                                                        "            catch (invalid_argument const &e) {\n"
                                                                        "                cerr << \"Bad input: invalid_argument thrown for " +
                                reference + ", using default Value if given\" << endl;\n"

                                            "            }\n"
                                            "            catch (out_of_range const &e) {\n"
                                            "                cerr << \"Integer overflow: out_of_range thrown for " +
                                reference + ", using default Value if given\" << endl;\n"
                                            "            }"
                                            "return " +
                                reference + "Int;\n";

                iM.methodName = "getValueOf" + reference;

                internalMethods.push_back(iM);
            }
            else if (convertTo == "Bool" || convertTo == "bool")
            {
                additionalParamVarName = reference + "Bool";
                internalMethod iM;
                iM.privacy = "public: ";
                iM.returnType = "bool";
                // iM.methodCode = "return bool" + interface + ";";

                iM.methodCode = "if(" + reference + "Param == \"true\" || " + reference + "Param == \"1\")\n"
                                                                                          "{\n" +
                                reference + "Bool = true;\n"
                                            "}\n"
                                            "else if(" +
                                reference +
                                "Param == \"false\" || " + reference + "Param == \"0\")\n"
                                                                       "{\n"
                                                                       "   " +
                                reference + "Bool = false;\n"
                                            "}\n"
                                            "else\n"
                                            "{\n"
                                            "cerr << \"bool wurde nicht im korrekten Format angegeben, erlaubt ist [true/1][false/0]! \" << endl;\n"
                                            "}\n"
                                            "return " +
                                reference + "Bool;\n";

                iM.methodName = "getValueOf" + reference;
                internalMethods.push_back(iM);
            }
            else
            {
                additionalParamVarName = reference + "Str";
                internalMethod iM;
                iM.privacy = "public: ";
                iM.returnType = "string";
                iM.methodCode = "return " + reference + "Param;\n";
                additionalParamVarName = reference + "Param";

                iM.methodName = "getValueOf" + reference;
                variableDefinitions += "bool boolIsSet" + reference + ";\n";

                internalMethods.push_back(iM);
            }
        }
    }

    if (((!connectToInternalMethod.empty() && interface.empty()) && !hasArguments.empty()) || ((!connectToExternalMethod.empty() && interface.empty()) && !hasArguments.empty()))
    {
        // Laut requirements sollte dann auch ein interface angegeben sein.
        cerr << "Es fehlt ein Interface bei \"" << reference << "!\n Code Generierung wird abgebrochen!\n Interface wird fuer die Getter Methode benoetigt, da zusaetzliche Parameter uebergeben werden koennen." << endl;
        exit(EXIT_FAILURE);
    }

    if (interface == "" && connectToInternalMethod == "" && connectToExternalMethod == "")
    {
        // Requirement Functional Nr. 20 ^^^^
        internalMethod iM;
        iM.privacy = "public: ";
        iM.returnType = "bool";

        iM.methodName = "isSet" + reference;
        boolIsSetName = "boolIsSet" + reference;
        globalVariables += "bool " + boolIsSetName + ";\n";

        iM.methodCode = "return isSet" + reference + "Bool;";

        internalMethods.push_back(iM);
    }

    if (connectToExternalMethod != "")
    {
        // Erstellen der externen Methoden
        externalMethod eM;

        eM.methodName = connectToExternalMethod;
        eM.privacy = "protected: ";
        eM.returnType = "virtual void";

        if (convertTo == "Integer" || convertTo == "integer")
        {
            eM.expectedVars = "int a";
        }
        else if (convertTo == "Bool" || convertTo == "bool")
        {
            eM.expectedVars = "bool b";
        }
        else
        {
            eM.expectedVars = "string s";
        }

        externalMethods.push_back(eM);
    }

    Code actOnArgs = Code(); // Code Objekt für die Zweite For-Schleife, in der die Argumente nach ihrer Überprüfung geparst werden

    actOnArgs.startIf(nameCheckBool);
    if (!connectToInternalMethod.empty())
    { // Code Generierung fuer connectToInternalMethod um die Methoden Aufzurufen
        internalMethod iM = internalMethod();

        iM.privacy = "private: ";

        iM.returnType = "void";

        iM.methodName = connectToInternalMethod;
        iM.methodCode = "cout << \"" + description + "\" << endl;\n";
        // cout << "METHOD NAME IN I_M: " << iM.methodName << endl;

        if (connectToInternalMethod == "printHelp")
        {
            iM.privacy = "protected: ";
            // internalMethods.push_back(iM);
            actOnArgs.addText(connectToInternalMethod +
                              "(signperlineInt);\n");
            if (!interface.empty())
            {
                actOnArgs.addText("isSet" + reference + "Bool = true;\n");
            }
        }
        else if (hasArguments != "")
        {
            if (convertTo == "Integer" || convertTo == "integer")
            {
                iM.expectedVars = "int " + additionalParamVarName;
            }
            else if (convertTo == "Bool" || convertTo == "bool")
            {
                iM.expectedVars = "bool " + additionalParamVarName;
            }
            else if (convertTo == "String" || convertTo == "string")
            {
                iM.expectedVars = "string " + additionalParamVarName;
            }
            else
            {
                std::cerr << "Da hasArguments und connectToInternalMethod gesetzt wurden, muss auch convertTo gesetzt werden! Bitte XML bei Option: " << reference << "ueberpruefen!" << endl;
                exit(EXIT_FAILURE);
            }

            actOnArgs.addText(connectToInternalMethod + "(" + additionalParamVarName + ");\n");
            if (!interface.empty())
            {
                actOnArgs.addText("isSet" + reference + "Bool = true;\n");
            }
        }
        internalMethods.push_back(iM);
    }
    else
    {
        actOnArgs.addText("cout << \"Es wurde der Parameter --" + longOpt +
                          " erfolgreich uebergeben!\" << endl;\n"); // Feedback print, wenn ein Argument angegeben wurde
        if (interface != "")
        {
            actOnArgs.addText("isSet" + reference + "Bool = true;\n");
        }
        if (!hasArguments.empty())
        {
            actOnArgs.addText(reference + "Param = " + reference + "Str;\n");
            actOnArgs.addText("cout << \"Zusaetzliche Argumente:\" << getValueOf" + reference +
                              "() << endl;\n"); // Zusaetzliche Argumente zur ueberpruefung mit ausgeben

            actOnArgs.addText(("isSet" + reference + "Bool = true;\n"));
        }
    }

    if (connectToExternalMethod != "")
    {
        // Code Generierung für den Aufruf der externen Methoden
        actOnArgs.addText(connectToExternalMethod + "(");

        if (convertTo == "")
        {
            std::cout << "convertTo" << endl;
            actOnArgs.addText(");\n");
        }

        else if (convertTo == "Integer" || convertTo == "integer")
        {
            actOnArgs.addText(reference + "Int);\n");
            std::cout << "convertTo = Int" << shortOpt << longOpt << endl;
        }
        else if (convertTo == "Bool" || convertTo == "bool")
        {
            actOnArgs.addText(reference + "Bool);\n");
            // std::cout << "convertTo = Bool" << shortOpt << longOpt << endl;
        }
        else
        {
            actOnArgs.addText(reference + "Param);\n");
            // std::cerr << "convertTo = String" << convertTo << shortOpt << longOpt << endl;
        }
    }
    actOnArgs.addText("continue;");
    actOnArgs.endIf();

    handleArgs += actOnArgs.code;
}
