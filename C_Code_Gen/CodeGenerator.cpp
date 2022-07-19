#include "CodeGenerator.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

/*
 * Diese Klasse soll dazu dienen, einfacher und übersichtlicher
 * ein Programm zu schreiben, welches als output c++ Code hat
 *
 *
 *
 *
 *
 *
 */

// Deklaration aller Strings, die benötigt werden, um den c++ Code zu generieren
////handleArgs////
// In handleArgs wird eine 2. For-Schliefe gespeichert, welche nach dem
// die Argumente auf ihre Korrektheit überprüft wurden nochmals alle Argumente
// durch-iteriert und nun auf die übergebenen Argumente reagiert.

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
     *Der generierte Code-String wird zurückgegeben
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
     * NUR FÜR LESBARKEIT!
     * Es wird eine geschweifte Klammer angehängt, um eine begonnene for-Schleife zu schließen
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
     * NUR FÜR LESBARKEIT!
     * Es wird eine geschweifte Klammer angehängt, um eine begonnene Verzweigung zu schließen
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

    string methodNames = "void myPrint(string myString, int newLineChecker);\n";

    for (int i = 0; i < internalMethods.size(); i++)
    {

        internalMethod iM = internalMethods[i];

        if (iM.methodName == "printHelp")
        {
            iM.expectedVars = "int signPerLine";
            iM.returnType = "protected:\nvirtual void ";
        }

        methodNames += iM.returnType + " " + iM.methodName + "(" + iM.expectedVars + ");\npublic:\n";
    }

    for (int i = 0; i < externalMethods.size(); i++)
    {
        externalMethod eM = externalMethods[i];

        methodNames += eM.returnType + " " + eM.methodName + "(" + eM.expectedVars + ") = 0;\npublic:\n";
    }

    // std::cout << methodNames << endl;

    return "#ifndef " + defString + "\n"
                                    "#define " +
           defString + "\n" + includesString +
           namespaceString +
           "namespace " + data.nameSpace.content + "\n" +
           "{\n" +
           "class " + data.className.content + "\n" +
           "{\n" +
           globalVariables +
           methodNames +
           "virtual void unknownOption(const string& unknown_option);" +
           "void parseOptions(int argc, char* argv[]);\n" +
           "};\n"
           "}\n"
           "#endif";
}

string Code::finalCode(xml_parser::GetOptSetup data)
{
    /*
     * Der Finale Code wird erstellt und zurückgegeben
     * Es werden hierfür alle entstandenen zwischen Strings zusammengefügt und zurückgegeben
     */
    ///:return: den gesamt Code {string}

    // std::cout << "Finmal: " << hFileName << endl;

    if (data.nameSpace.content.empty())
    {
        return includesString +
               "#include \"" + data.headerFileName.content + "\"\n" +
               namespaceString +
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
               "}\n";
    }
    else
    {
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
     * Alle Implementierungen werden in einem gesamt String gespeichert und zurückgegeben
     */

    ///:return: die Implementierung aller Methoden {string}

    Code methods = Code();

    string methodNames;

    ///////////////////////myPrint für signPerLine erstellen

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
            "printHelp") ////HelpMethode wird erstellt
        {
            iM.expectedVars = "int signPerLine";
            iM.methodName = data.className.content + "::" + iM.methodName;
            if (!authorCodeAdded)
            {
                printHelpMethodCode += "myPrint(\"\\n\", getValueOfsignperline());";
                printHelpMethodCode += "myPrint(\"Sample Usage:\\n\", getValueOfsignperline());";
                for (int ij = 0; ij < data.sampleUsage.sample.size(); ij++)
                {
                    printHelpMethodCode += "myPrint(\"" + data.sampleUsage.sample[ij].content + "\\n\", getValueOfsignperline());";
                }
                printHelpMethodCode += "myPrint(\"\\n\", getValueOfsignperline());";
                printHelpMethodCode += "myPrint(\"Overall-Description:\\n\", getValueOfsignperline());";
                for (int ij = 0; ij < data.overAllDescription.block.size(); ij++)
                {
                    printHelpMethodCode += "myPrint(\"" + data.overAllDescription.block[ij].content + "\\n\", getValueOfsignperline());";
                }
                printHelpMethodCode += "myPrint(\"\\n\", getValueOfsignperline());";
                printHelpMethodCode += "myPrint(\"Author Name: " + data.author.name + ", \", getValueOfsignperline());\n";
                printHelpMethodCode += "myPrint(\"Author Mail: " + data.author.mail + ", \", getValueOfsignperline());\n";
                printHelpMethodCode += "myPrint(\"Author Phone: " + data.author.phone + "\\n\", getValueOfsignperline());\n";
                authorCodeAdded = true;
            }

            iM.methodCode = "cout<<\"" + sampleUsage + "\"<< endl;\n" + printHelpMethodCode;

            methods.addText("void " + iM.methodName + "(int signPerLine)\n{\n");
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
                           "();\n"; /////////////////////////////////////////////////////////////////////////
        }                           ////H Datei
        // ofstream MyFile(headerFileName);

        // Write to the file
        // MyFile << "Some hFile Text...";

        // Close the file
        // MyFile.close();
        ////H Datei Ende
        // cout << "NAMES: \n" << methodNames<< endl;                                                                /////////////////////////////////////////////////////////////////////////
    }

    return methods.code;
}

vector<string> Code::split(string str, char seperator)
{
    /*
     * Custom Split - Methode, um einen String bei einem bestimmten Char zu trennen
     * gibt einen Vektor mit allen Elementen zwischen den Seperatoren zurück
     */
    ///:param str: Der zu trennende String
    ///:param seperator: der Char, an dem der String getrennt werden soll
    ///:return: Vector mit allen Substrings {Vector<string>}

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
                    data.options.option[i].connectToExternalMethod);
    }

    endForLoop(); // For Schleife fertig, der  rest kommt in finalCode()

    string filename = "newFile"; // Optional damit keine Fehler auftreten

    // EXIT TEST: exit(EXIT_SUCCESS)

    // cout << "CODE: " << endl
    //   << finalCode();                                                                       //Code ausgeben

    // Create and open a text file
    ofstream MyFile(data.sourceFileName.content);

    // Write to the file
    MyFile
        << finalCode(data); // Code in Datei schreiben

    // Close the file
    MyFile.close();

    ofstream MyHeaderFile(data.headerFileName.content);

    // Write to the file
    MyHeaderFile
        << finalHeaderCode(data); // Code in Datei schreiben

    // Close the file
    MyHeaderFile.close();
}

void Code::addArgument(string ref,
                       string shortOpt,
                       string longOpt,
                       string exclusion, // DONE
                       string connectToInternalMethod,
                       string description,
                       string interface,
                       string hasArguments, // DONE
                       string convertTo,
                       string defaultValue,            // DONE
                       string connectToExternalMethod) // Funktion, die alle Argumente aus der xml annimmt
{
    /*cout << "********************************************" << endl;
    cout << "ref: " << ref << endl;
    cout << "shortOpt: " << shortOpt << endl;
    cout << "longOpt: " << longOpt << endl;
    cout << "exclusion: " << exclusion << endl;
    cout << "connectToiM: " << connectToInternalMethod << endl;
    cout << "connectToeM: " << connectToExternalMethod << endl;
    cout << "description: " << description << endl;
    cout << "interface: " << interface << endl;
    cout << "hasArguments: " << hasArguments << endl;
    cout << "convertTo: " << convertTo << endl;
    cout << "defaultValue: " << defaultValue << endl;
    cout << "********************************************" << endl;*/
    /*
     * Es wird zunächst ein String generiert, welcher in eine if-Abfrage eingefügt werden kann, um zu überprüfen,
     * ob das aktuelle Argument der Iteration dem gewünschten String entspricht (shortOpt/longOpt)
     *
     * Wenn "exclusion" gesetzt wurde, wir der übergeben String bei dem char ',' aufgetrennt
     * und es wird Code generiert, welcher nun prüft, ob die gesetzten Exclusions bereits existieren.
     * Anschließend wird Code generiert, welcher das Argument selbst "registriert" für zukünftige
     * exclusion - checks.
     */

    if (headerFileName.empty())
    {
        std::cerr << "Es muss ein Name für die Header-Datei in der XML-Datei angegeben werden!" << endl;
        exit(EXIT_SUCCESS);
    }

    if (sourceFileName.empty())
    {
        std::cerr << "Es muss ein Name für die Source-Code-Datei in der XML-Datei angegeben werden!" << endl;
        exit(EXIT_SUCCESS);
    }

    string reference;
    size_t found = longOpt.find('-');
    if (found != string::npos)
    {
        reference = longOpt;
        reference.erase(remove(reference.begin(), reference.end(), '-'), reference.end()); // remove A from string
        // std::cout << "lOpt: " << longOpt << ", reference: " << reference << endl;
        // std::cout << "found '-' in " << longOpt << endl;
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

    string codeArgParse;
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
        // exclusions werden in dem Format "1,2,3,4,..." übergeben
        // dieser String wird jeweils an einem Komma getrennt und die einzelnen Elemente
        // in dem Vector exclusions als Integer gespeichert

        vector<string> exclusionStrings = split(exclusion,
                                                ','); // Der String wird aufgetrennt

        Code exclCode = Code(); // Es wird eine instanz der Klasse Code erzeugt, um den zu generierenden Code
        // lesbarer, bzw. übersichtlicher erstellen zu können

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

        tempCode += "for (int j = 0; j < exclusionValuesSorted.size(); j++)";
        tempCode += "\n{";
        tempCode += "vector<string> tempExclusionVec = exclusionValuesSorted[j];";
        tempCode += "for (int k = 0; k < tempExclusionVec.size(); k++)";
        tempCode += "\n{";
        tempCode += "for (int m = 0; m < localExclusions.size(); m++)";
        tempCode += "\n{";
        tempCode += "if (localExclusions[m] == tempExclusionVec[k])";
        tempCode += "\n{";
        tempCode += "cout << \"--" + reference + " ist nicht erlaubt mit \" + argumentnames[j];";
        tempCode += "\nexit(EXIT_FAILURE);";
        tempCode += "\n}\n}\n}\n}";

        // Die Exclusions wurden überprüft
        if (ref != "")
        {
            tempCode += "vector<string> temp = {\"" + ref + "\"};\n";
            tempCode += "exclusionValuesSorted.push_back(temp);\n";
        }
        else
        {
            tempCode += "exclusionValuesSorted.push_back(localExclusions);\n";
        }

        tempCode += "argumentnames.push_back(\"--" + reference + "\");\n";
        // Code zur Vektor-Generierung ist erstellt
        exclCode.addText(tempCode); // Code wird in in den Code zur Exclusion-Überprüfung eingefügt

        /*exclCode.startForLoop(
            "int j = 0; j < exclusions.size(); j++"); // Code wird mit Einrückungen lesbar eingefügt
        exclCode.startForLoop("int k = 0; k < localExclusions.size(); k++");
        exclCode.startIf("to_string(exclusions[i]) == localExclusions[j]");
        // exclCode.addText("cout << \"Es wurde eine ungültige Kombination von Argumenten angegeben!\" << endl;\n");

        exclCode.addText("cerr <<  \"" + reference +
                         " und \"<< refValues[exclusions[j]]<<\" sind nicht zusammen erlaubt!\" << endl;\n");

        exclCode.addText("exit(EXIT_FAILURE);\n");
        exclCode.endIf();
        exclCode.endForLoop();

        exclCode.startIf("noRef == 1");
        // exclCode.addText("cerr << \"Es wurde ein Argument übergeben, dass Ref 1-3 nicht zulässt, --help ist somit verboten!\"<< endl;\n");
        exclCode.addText("cerr <<  \"" + reference +
                         " und \"<< refValues[exclusions[j]]<<\" sind nicht zusammen erlaubt!\" << endl;\n");
        exclCode.addText("exit(EXIT_FAILURE);\n");
        exclCode.endIf();

        exclCode.endForLoop();

        exclCode.startForLoop("int j = 0; j < localExclusions.size(); j++");
        exclCode.addText("exclusions.push_back(stol(localExclusions[j]));");
        exclCode.endForLoop();

        exclCode.startIf("exitArg != 1");
        if (!ref.empty())
        {
            exclCode.addText("exclusions.push_back(" + ref +
                             ");\n"); // Das eigene Argument wird "registriert"
            if (interface != "")
            {
                exclCode.addText("refValues[" + ref + "] = \"" + interface + "\";");
            }
            else if (longOpt != "")
            {
                exclCode.addText("refValues[" + ref + "] = \"" + longOpt + "\";");
            }
            else
            {
                exclCode.addText("refValues[" + ref + "] = \"" + shortOpt + "\";");
            }
        }
        exclCode.addText("noRef = 1;\n");
        exclCode.endIf();*/

        exclusionCheck += ifStateStart;
        exclusionCheck += exclCode.getCode();

        if (hasArguments == "Required" || hasArguments == "optional")
        {

            exclusionCheck += "if(i+1 < argc)\n{\n" + reference +
                              "Str = argv[i+1];\n}\n"; // Code Generierung um zusätzliche Argumente einzulesen, falls diese Möglich sein sollen
            if (hasArguments == "Required")
            {
                exclusionCheck += "else\n{";
                exclusionCheck += "cout << \"--" + longOpt + " benötigt ein zusätzliches Argument!\\n\"\n\"\" << endl;\nexit(EXIT_FAILURE);\n\n";
                exclusionCheck += "cerr << \"ERROR: --" + longOpt + " benötigt ein zusätzliches Argument!\\n\"\n\"\" << endl;\nexit(EXIT_FAILURE);\n}\n";
            }

            exclusionCheck += "additionalParams.push_back(" + reference + "Str);\n";
        }
        exclusionCheck += "}\n";
    }
    else if (ref != "")
    {
        exclusionCheck += "vector<string> temp = {\"" + ref + "\"};\n";
        exclusionCheck += "exclusionValuesSorted.push_back(temp);\n";

        exclusionCheck += "argumentnames.push_back(\"--" + reference + "\");\n";
        // exclCode.addText(tempCode);
    }
    ///////////////////////////////////////////////////////////////////////////
    if (hasArguments ==
        "Required") // Code Generierung, um zu überprüfen, ob ein zusätzliches Argument angegeben wurde,
    // wenn es required ist
    {
        Code pathCheckCode = Code(); ////pathCheckCode////
        // Neue Instanz von Code() um zu generierenden Code zwischenzuspeichern

        variableDefinitions += "string " + reference + "Str;\n";

        pathCheckCode.startIf("!" + reference + "Str.empty() && " + reference + "Str.length() > 1");
        pathCheckCode.startIf(
            "(" + reference + "Str.at(0) == '-') || " + reference +
            "Str.length() <= 1");
        pathCheckCode.addText("cout << \"--" + longOpt + " benötigt ein zusätzliches Argument!\\n Da der nächste Parameter mit einem '-' startet, oder zu kurz (<1) ist, wurde kein zusaetzliches Argument erkannt!\"\n\"\" << endl;\n");
        pathCheckCode.addText("cerr << \"ERROR: --" + longOpt + " benötigt ein zusätzliches Argument!\\n Da der nächste Parameter mit einem '-' startet, oder zu kurz (<1) ist, wurde kein zusaetzliches Argument erkannt!\"\n\"\" << endl;\n");
        pathCheckCode.addText("exit(EXIT_FAILURE);\n");
        pathCheckCode.endIf();
        pathCheckCode.endIf();

        /*pathCheckCode.startIf(reference +"Str.length() == 1");
            pathCheckCode.addText("cout << \"" +longOpt +" benötigt ein zusätzliches Argument!\" << endl;\n");
            pathCheckCode.addText("exitArg = 1;\n");
        pathCheckCode.endIf(); */

        pathRequiredCheck += pathCheckCode.getCode();
    }

    if (hasArguments ==
        "optional") // Code Generierung, um zu überprüfen, ob ein zusätzliches Argument angegeben wurde,
    // wenn es required ist
    {
        Code pathCheckCode = Code(); ////pathCheckCode////
        // Neue Instanz von Code() um zu generierenden Code zwischenzuspeichern

        if (defaultValue == "")
        {
            variableDefinitions += "string " + reference + "Str;\n";
        }
        /////////////////////////////////////////////////////////////////
        if (!defaultValue.empty()) // Code Generierung, falls es default Parameter gibt
        {
            variableDefinitions += "string " + reference + "Str = \"" + defaultValue + "\";\n";
        }
        //////////////////////////////////////////////////////////////////

        pathCheckCode.startIf("!" + reference + "Str.empty() && " + reference + "Str.length() > 1");
        pathCheckCode.startIf(
            "(" + reference + "Str.at(0) == '-' && " + reference + "Str.at(1) == '-') || " + reference +
            "Str.length() <= 1");
        pathCheckCode.addText(
            "cout << \"zu --" + longOpt + " wurde kein zusätzliches Argument übergeben, default-Wert: " +
            defaultValue + " wird übernommen!\"<< endl;\n");
        pathCheckCode.endIf();
        pathCheckCode.endIf();

        /*pathCheckCode.startIf(reference +"Str.length() == 1");
        pathCheckCode.addText("cout << \"" +longOpt +" benötigt einen Pfad als Argument!\" << endl;\n");
        pathCheckCode.addText("exitArg = 1;\n");
        pathCheckCode.endIf();*/

        pathRequiredCheck += pathCheckCode.getCode();
    }

    // Code Generierung für convertToInt mit try-catch
    if (convertTo == "Integer")
    {
        // variableDefinitions += "int " + interface + "Int = 0;\n";
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

    } ////////////////////////////////////////////////////////////////////////

    if (convertTo == "Bool")
    {
        // std::cout << "convertToBool" << endl;
        if (defaultValue != "")
        {
            globalVariables += "bool " + reference + "Bool = " + defaultValue + ";\n";
            additionalParamVarName = reference + "Bool";

            // std::cout << "addparamVarName: " << additionalParamVarName << endl;
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

    // zum gesamt Code hinzufügen

    if (!shortOpt.empty() && !longOpt.empty())
    {
        printHelpMethodCode += "myPrint(\"-" + shortOpt + ", --" + longOpt + "\\n\", getValueOfsignperline());\n";
    } // Die Description wird an einen globalen string hinzugefügt für die printHelp Methode

    if (shortOpt.empty() && !longOpt.empty())
    {
        printHelpMethodCode += "myPrint(\"--" + longOpt + "\\n\", getValueOfsignperline());\n";
    }

    if (!shortOpt.empty() && longOpt.empty())
    {
        printHelpMethodCode += "myPrint(\"--" + shortOpt + "\\n\",  getValueOfsignperline());\n";
    }

    printHelpMethodCode += "myPrint(\"  " + description + "\\n\\n\", getValueOfsignperline());\n";

    if (!interface.empty())
    {

        globalVariables += "bool isSet" + reference + "Bool;\n";

        internalMethod iM;

        iM.methodName = "isSet" + reference;

        iM.methodCode = "return isSet" + reference + "Bool;\n";
        iM.returnType = "bool";

        internalMethods.push_back(iM);

        if (hasArguments != "")
        {
            // std::cout << reference << "                                                                                                                         hasArguments!" << endl;
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
            if (convertTo == "Integer")
            {
                additionalParamVarName = reference + "Int";
                internalMethod iM;
                iM.returnType = "int";
                // iM.methodCode = "return " + reference + "Int;\n"; Kommt jetzt im großen string im Anschluss

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
            else if (convertTo == "Bool")
            {
                additionalParamVarName = reference + "Bool";
                internalMethod iM;
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
        cerr << "Es fehlt ein Interface bei \"" << reference << "!\n Code Generierung wird abgebrochen!\n Interface wird für die Getter Methode benötigt, da zusätzliche Parameter übergeben werden können." << endl;
        exit(EXIT_FAILURE);
    }

    if (interface == "" && connectToInternalMethod == "" && connectToExternalMethod == "")
    {
        internalMethod iM;
        iM.returnType = "bool";

        iM.methodName = "isSet" + reference; // Da durch das - im Namen Probleme auftreten
        boolIsSetName = "boolIsSet" + reference;
        globalVariables += "bool " + boolIsSetName + ";\n";

        iM.returnType = "bool";

        iM.methodCode = "return isSet" + reference + "Bool;";

        internalMethods.push_back(iM);
    }

    if (connectToExternalMethod != "")
    {
        externalMethod eM;

        eM.methodName = connectToExternalMethod;
        eM.returnType = "virtual void";

        if (convertTo == "Integer")
        {
            eM.expectedVars = "int a";
        }
        else if (convertTo == "Bool")
        {
            eM.expectedVars = "bool b";
        }
        else
        {
            eM.expectedVars = "string s";
        }

        externalMethods.push_back(eM);
    }

    Code actOnArgs = Code();

    actOnArgs.startIf(nameCheckBool);
    if (!connectToInternalMethod.empty()) /////////////////////////////////////////////////////////////////////////
    {                                     // Code Generierung für connectToInternalMethod
        internalMethod iM = internalMethod();

        iM.methodName = connectToInternalMethod;
        iM.methodCode = "cout << \"" + description + "\" << endl;\n";
        // cout << "METHOD NAME IN I_M: " << iM.methodName << endl;

        if (connectToInternalMethod == "printHelp")
        {
            internalMethods.push_back(iM);
            actOnArgs.addText(connectToInternalMethod +
                              "(signperlineInt);\n"); ///############################HARD CODED nicht gut
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
                std::cerr << "Da hasArguments und connectToInternalMethod gesetzt wurden, muss auch convertTo gesetzt werden! Bitte XML bei Option: " << reference << "überprüfen!" << endl;
                exit(EXIT_FAILURE);
            }
            internalMethods.push_back(iM);
            actOnArgs.addText(connectToInternalMethod + "(" + additionalParamVarName + ");\n");
            if (!interface.empty())
            {
                actOnArgs.addText("isSet" + reference + "Bool = true;\n");
            }
        }
    }
    else
    {
        actOnArgs.addText("cout << \"Es wurde der Parameter --" + longOpt +
                          " erfolgreich übergeben!\" << endl;\n"); // Feedback print, wenn ein Argument angegeben wurde
        if (interface != "")
        {
            actOnArgs.addText("isSet" + reference + "Bool = true;\n");
        }
        if (!hasArguments.empty())
        {
            actOnArgs.addText(reference + "Param = " + reference + "Str;\n");
            actOnArgs.addText("cout << \"Zusätzliche Argumente:\" << getValueOf" + reference +
                              "() << endl;\n"); // Zusätzliche Argumente zur Überprüfung mit ausgeben

            actOnArgs.addText(("isSet" + reference + "Bool = true;\n"));
        }
    }

    if (connectToExternalMethod != "")
    {
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
            std::cout << "convertTo = Bool" << shortOpt << longOpt << endl;
        }
        else
        {
            actOnArgs.addText(reference + "Param);\n"); // Beim Testen schauen, obs funktioniert, sonst Str statt Param anhängen!!!
            std::cerr << "convertTo = String" << convertTo << shortOpt << longOpt << endl;
        }
    }
    actOnArgs.addText("continue;");
    actOnArgs.endIf();

    handleArgs += actOnArgs.code;
}