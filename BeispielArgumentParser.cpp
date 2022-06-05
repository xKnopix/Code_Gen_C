#include <string>
#include <iostream>
#include <Vector>

using namespace std;

//Methoden zur Ausgabe am Ende
//methode für Argument --h/--help
void printHelp()                                                                               //interne Methode für printHelp (Ist die hier überhaupt richtig??)
{
    cout << "Hilfe wird ausgegeben..." << endl;
}
//methode für Argument --v/--Version
void printVersion()                                                                            //Abwarten, ob extern, oder intern gefordert, wo bekommt man die Versionsnummer eigentlich her??
{
    cout << "Version wird ausgegeben..." << endl;
}
//methode für Argument parse-only
void ParseXML()                                                                                 
{
    cout << "XML wird geparsed..." << endl;
}








int main(int argc, char* argv[])
{                                                               
    vector<int> exclusions;                                                      //Speichern, welche Ref-Nummern gesetzt sind, um die Exclusions abfragen zu können
    int exitArg = 0;                                                                       //Wenn exit während der Überprüfung auf 1 gesetzt wird, wird das Programm nach der Überprüfung beendet
    int noRef = -1;                                                                     //-1: nicht gesetzt, 0: Die Optionen Ref 1-3 (gesamt) dürfen vorkommen, 1: Die Optionen Ref 1-3(gesamt) dürfen nicht vorkommen

    string outPath;                                                                     //String für das Argument für den Ausgabe Pfad
    string astylePath;                                                                  //String für das Argument für den Astyle Pfad
    string signPerLine = "79";                                                          //string für das Argument für signPerLine


    if(argc==1)                                                                         //Wenn kein Argument übergeben wurde Hinweis geben
    {
        cout << "Usage: ./program_name arg1" << endl;
    }
    else
    {
        for(int i = 1; i<argc; i++)                                                     //for-Schleife, um alle eingegebenen Argumente abzuarbeiten
        {
            //cout << argv[i] << endl;                                                    

            ////////////////
            if(string(argv[i]) == "--h" || string(argv[i]) == "--help")                 //Wenn Parameter --help oder --h gesetzt ist
            {
                /*
                Ref = 1
                shortOpt = h
                longOpt = help
                exclusion 2, 3
                connectTointernalMethod = printHelp
                Description = "Diese Hilfe ausgeben und beenden"
                */
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                vector<string> localExclusions = {"1", "2"}; //DONE//

                for(int i = 0; i < exclusions.size(); i++)
                {
                    for(int j = 0; j < localExclusions.size(); j++)
                    {
                        if(to_string(exclusions[i]) == localExclusions[j])
                        {
                            cout << "Es wurde eine ungültige Kombination von Argumenten angegeben!" << endl;
                            exitArg = 1;
                        }
                    }
                }                                                                                                   //DONE//

                if(noRef == 0)                                                      //Schauen, ob eine der Optionen gesetzt ist, die Ref 1-3 ausschließt
                {
                    cout << "Es wurde ein Argument übergeben, dass Ref 1-3 nicht zulässt, --help ist somit verboten!"<< endl;
                    exitArg = 1;
                }

                if(exitArg != 1)
                {
                    exclusions.push_back(1);
                    noRef = 1;
                }
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                /*
                if(exclusion[2]!=0)                                                      //Exclusion 2 überprüfen -> verboten
                {
                    cout << "--help ist nicht erlaubt mit Ref 2!" << endl;
                    exitArg = 1;
                }
                else if(exclusion[3]!=0)                                                 //Exclusion 3 überprüfen -> verboten
                {
                    cout << "--help ist nicht erlaubt mit Ref 3!" << endl;
                    exitArg = 1;
                }
                else
                {    
                    exclusion[1] = 1;                                                   //Exclusion-Array setzen, für spätere überprüfungen bei anderen Argumenten

                }
                 */
            }

            if(string(argv[i]) == "--v" || string(argv[i]) == "--Version")              //Wenn Parameter --Version oder --v gesetzt ist
            {
                /*
                Ref = 2
                shortOpt = v
                longOpt = Version
                exclusion 1, 3
                connectTointernalMethod = printVersion
                Description = "Gibt die Version des Programms aus und beendet"
                */
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                vector<string> localExclusions = {"1", "2"};

                for(int i = 0; i < exclusions.size(); i++)
                {
                    for(int j = 0; j < localExclusions.size(); j++)
                    {
                        if(to_string(exclusions[i]) == localExclusions[j])
                        {
                            cout << "Es wurde eine ungültige Kombination von Argumenten angegeben!" << endl;
                            exitArg = 1;
                        }
                    }
                }

                if(noRef == 0)                                                      //Schauen, ob eine der Optionen gesetzt ist, die Ref 1-3 ausschließt
                {
                    cout << "Es wurde ein Argument übergeben, dass Ref 1-3 nicht zulässt, --help ist somit verboten!"<< endl;
                    exitArg = 1;
                }

                if(exitArg != 1)
                {
                    exclusions.push_back(1);
                    noRef = 1;
                }
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
            }

            if(string(argv[i]) == "--out-path")                                           //Wenn Parameter Out-Path gesetzt ist
            {
                /*
                longOpt = out-path
                hasArguments = required
                exclusion = 1, 2, 3
                interface = OutputPath
                Description = "Der Pfad wo das Ergebnis hingenriert werden soll (sonst ins aktuelle Verzeichnis)"
                */
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                vector<string> localExclusions = {"1", "2"};

                for(int i = 0; i < exclusions.size(); i++)
                {
                    for(int j = 0; j < localExclusions.size(); j++)
                    {
                        if(to_string(exclusions[i]) == localExclusions[j])
                        {
                            cout << "Es wurde eine ungültige Kombination von Argumenten angegeben!" << endl;
                            exitArg = 1;
                        }
                    }
                }

                if(noRef == 0)                                                      //Schauen, ob eine der Optionen gesetzt ist, die Ref 1-3 ausschließt
                {
                    cout << "Es wurde ein Argument übergeben, dass Ref 1-3 nicht zulässt, --help ist somit verboten!"<< endl;
                    exitArg = 1;
                }

                if(exitArg != 1)
                {
                    exclusions.push_back(1);
                    noRef = 1;
                }
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
            }

            if(string(argv[i]) == "--astyle-path")                                              //Wenn Parameter astyle-path gesetzt ist
            {
                /*
                longOpt = astyle-path
                hasArguments = required
                interface = AstylePath
                exclusion = 1, 2, 3
                Description = "Der Pfad wo die Astyle executable gefunden werden kann"
                */
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                vector<string> localExclusions = {"1", "2"};

                for(int i = 0; i < exclusions.size(); i++)
                {
                    for(int j = 0; j < localExclusions.size(); j++)
                    {
                        if(to_string(exclusions[i]) == localExclusions[j])
                        {
                            cout << "Es wurde eine ungültige Kombination von Argumenten angegeben!" << endl;
                            exitArg = 1;
                        }
                    }
                }

                if(noRef == 0)                                                      //Schauen, ob eine der Optionen gesetzt ist, die Ref 1-3 ausschließt
                {
                    cout << "Es wurde ein Argument übergeben, dass Ref 1-3 nicht zulässt, --help ist somit verboten!"<< endl;
                    exitArg = 1;
                }

                if(exitArg != 1)
                {
                    exclusions.push_back(1);
                    noRef = 1;
                }
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
            }

            if(string(argv[i]) == "--sign-per-line")
            {
                /*
                longOpt = sign-per-line
                hasArguments = optional
                interface = SignPerLine
                Exclusion = 1, 2, 3
                convertTo = Integer
                defaultValue = 79
                Description = "Die Anzahl der Zeichen pro Linie für den Helptext. Ohne Argument wird der Standartwert genommen."
                */
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                vector<string> localExclusions = {"1", "2"};

                for(int i = 0; i < exclusions.size(); i++)
                {
                    for(int j = 0; j < localExclusions.size(); j++)
                    {
                        if(to_string(exclusions[i]) == localExclusions[j])
                        {
                            cout << "Es wurde eine ungültige Kombination von Argumenten angegeben!" << endl;
                            exitArg = 1;
                        }
                    }
                }

                if(noRef == 0)                                                      //Schauen, ob eine der Optionen gesetzt ist, die Ref 1-3 ausschließt
                {
                    cout << "Es wurde ein Argument übergeben, dass Ref 1-3 nicht zulässt, --help ist somit verboten!"<< endl;
                    exitArg = 1;
                }

                if(exitArg != 1)
                {
                    exclusions.push_back(1);
                    noRef = 1;
                }
                if(i+1 != argc)
                {
                    signPerLine = argv[i+1];
                }

                ////////////////////////////////////////////////////////////////////////////////////////////////////////
            }
        
            if(string(argv[i]) == "--n" || string(argv[i]) == "--only-if-newer")
            {
                /*
                shortOpt = n
                longOpt = only-if-newer
                interface = OnlyIfNewer
                exclusion = 1, 2, 3
                Description = "Generiert nur wenn die Eingangsdatei neuer ist wie die bereits generierte"
                */
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                vector<string> localExclusions = {"1", "2"};

                for(int i = 0; i < exclusions.size(); i++)
                {
                    for(int j = 0; j < localExclusions.size(); j++)
                    {
                        if(to_string(exclusions[i]) == localExclusions[j])
                        {
                            cout << "Es wurde eine ungültige Kombination von Argumenten angegeben!" << endl;
                            exitArg = 1;
                        }
                    }
                }

                if(noRef == 0)                                                      //Schauen, ob eine der Optionen gesetzt ist, die Ref 1-3 ausschließt
                {
                    cout << "Es wurde ein Argument übergeben, dass Ref 1-3 nicht zulässt, --help ist somit verboten!"<< endl;
                    exitArg = 1;
                }

                if(exitArg != 1)
                {
                    exclusions.push_back(1);
                    noRef = 1;
                }
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
            } 
        
            if(string(argv[i]) == "--no-format")
            {
                /*
                longOpt = no-format
                interface = noFormat
                exclusion = 1, 2, 3
                Description = "Erzeugte Datei wird nicht formatiert
                */

                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                vector<string> localExclusions = {"1", "2"};

                for(int i = 0; i < exclusions.size(); i++)
                {
                    for(int j = 0; j < localExclusions.size(); j++)
                    {
                        if(to_string(exclusions[i]) == localExclusions[j])
                        {
                            cout << "Es wurde eine ungültige Kombination von Argumenten angegeben!" << endl;
                            exitArg = 1;
                        }
                    }
                }

                if(noRef == 0)                                                      //Schauen, ob eine der Optionen gesetzt ist, die Ref 1-3 ausschließt
                {
                    cout << "Es wurde ein Argument übergeben, dass Ref 1-3 nicht zulässt, --help ist somit verboten!"<< endl;
                    exitArg = 1;
                }

                if(exitArg != 1)
                {
                    exclusions.push_back(1);
                    noRef = 1;
                }
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
            }
        
            if(string(argv[i]) == "--parse-only")
            {
                /*
                Ref = 3
                longOpt = parse-only
                hasArguments = required
                connectToInternalMethod = ParseXML
                exclusion = 1, 2
                Description = "Parst die Datei einmal und beendet das Programm
                */
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                vector<string> localExclusions = {"1", "2"};

                for(int i = 0; i < exclusions.size(); i++)
                {
                    for(int j = 0; j < localExclusions.size(); j++)
                    {
                        if(to_string(exclusions[i]) == localExclusions[j])
                        {
                            cout << "Es wurde eine ungültige Kombination von Argumenten angegeben!" << endl;
                            exitArg = 1;
                        }
                    }
                }

                if(noRef == 0)                                                      //Schauen, ob eine der Optionen gesetzt ist, die Ref 1-3 ausschließt
                {
                    cout << "Es wurde ein Argument übergeben, dass Ref 1-3 nicht zulässt, --help ist somit verboten!"<< endl;
                    exitArg = 1;
                }

                if(exitArg != 1)
                {
                    exclusions.push_back(1);
                    noRef = 1;
                }
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
            }
        }

        //Schauen, ob die required Arguments mitgegeben wurden, oder, ob ein Argument mit -- folgt, in diesem Fall liegt ein Fehler vor(hasArgument=required), außer bei signPerLine(hasArgument=optional)
        if(!outPath.empty())
        {
            if(outPath.at(0) == '-' && outPath.at(1) == '-')
            {
            cout << "--out-path benötigt den Ausgabepfad als Argument!" << endl;
                exitArg = 1;
            }
        }

        if(!astylePath.empty())
        {
           if(astylePath.at(0) == '-' && astylePath.at(1) == '-')
            {
                cout << "--astyle-path benötigt den Pfad zu astyle als Argument!" << endl;
                exitArg = 1;
            } 
        }
        

        //Try-Catch um signPerLine von String zu Int umzuwandeln
        try 
        {
        int signPerLineInt = std::stol(signPerLine);
        //std::cout << i << std::endl;
        cout <<"sPLInt: " << signPerLineInt << endl;
        }
        catch (std::invalid_argument const &e)
        {
            std::cout << "Bad input: std::invalid_argument thrown for sign-per-line" << std::endl;
            exitArg = 1;
        }
        catch (std::out_of_range const &e)
        {
            std::cout << "Integer overflow: std::out_of_range thrown for sign-per-line" << std::endl;
            exitArg = 1;
        }
        cout << "Code after Catch" << endl;

        //schauen, ob exit auf 1 gesetzt wurde, Fehlermeldung sollte jeweils, bevor exit auf 1 gesetzt wird ausgegeben worden sein
        if(exitArg > 0)
        {
            cout << "EXIT" << endl;
            return 0;
        }

        //jetzt sollten die angegebenen Argumente eigentlich stimmen
        
        //jetzt kann man alle argumente nochmals mit einer Forschleife durchgehen, und dann, da jetzt jaalles geprüft wurde auf die Argumente "reagieren (prints, variablen setzen(signPerLine) etc...),
        //bis jetzt hab ich aber mal nur die Prints gemacht
        for(int i = 1; i<argc; i++)
        {
            if(string(argv[i]) == "--help" || string(argv[i]) == "--h")
            {
                printHelp();
            }

            if(string(argv[i]) == "--version" || string(argv[i]) == "--v")
            {
                printVersion();
            }

            if(string(argv[i]) == "--parse-only")
            {
                ParseXML();
            }
        }
        cout << "Code ist durchgelaufen" << endl;

    }
    
    return 0;
}




//Frage: warum ist out-path hasArguments = required (in der XML), in der Description steht ja: " ...'sonst' ins aktuelle Verzeichnis"???
//Was ist mit interface bei den <Optionen/> in der XML gemeint? muss man da auch noch was implementieren?