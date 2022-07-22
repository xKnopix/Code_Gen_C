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
        bool isSetastylepathBool;       /// Bool zum prüfen, ob der Parameter astyle-path gesetzt wurde
        string astylepathParam;         /// String zum speichern des zusätzlichen Argumentes von Astyle-Path
        bool isSetonlyifnewerBool;      /// Bool zum prüfen, ob der Parameter only-if-newer gesetzt wurde
        bool isSetnoformatBool;         /// Bool zum prüfen, ob der Parameter no-format gesetzt wurde
        bool isSetoutpathBool;          /// Bool zum prüfen, ob der Parameter out-path gesetzt wurde
        string outpathParam;            /// String zum speichern des zusätzlichen Argumentes von out-path
        bool parseonlyBool = 0;         /// Bool zum konvertieren von dem zusätzlichen Argument bei parse-only
        bool isSetparseonlyBool;        /// Bool zum prüfen, ob der Parameter parse-only gesetzt wurde
        string parseonlyParam;          /// String zum speichern des zusätzlichen Argumentes von parse-only
        int signperlineInt = 79;        /// Integer zum konvertieren von dem zusätzlichen Argument bei sign-per-line (Defaultwert wird direkt gesetzt)
        bool isSetsignperlineBool;      /// Bool zum prüfen, ob der Parameter sign-per-line gesetzt wurde
        string signperlineParam = "79"; /// String zum speichern des zusätzlichen Argumentes von sign-per-line
        int versionInt = 0;             /// Integer zum konvertieren von dem zusätzlichen Argument bei version (Defaultwert wird direkt gesetzt)
        bool isSetversionBool;          /// Bool zum prüfen, ob der Parameter version gesetzt wurde

        /// Funktion, um dem Text mit einer bestimmten Zeilenlänge auzugeben.
        ///
        /// Diese Funktion gibt den übergebenen String aus, und fügt, nachdem die maximale Anzahl an Zeichen erreicht wurde ein 'Carriage-return' ein.
        ///@param myString Der String, der ausgegeben werden soll
        ///@param newLineChecker Die maximale Zeilenlänge in Zeichen
        ///@returns void
        /// \n **Beispiel Anwendung:**
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
        /// myPrint("Das ist ein Test für sign-per-line", 5);
        ///
        /// OUTPUT:
        ///
        /// Das i
        /// st ei
        /// n Tes
        /// t für
        /// sign-
        /// per-l
        /// ine
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~
        ///@author Jacob
    private:
        void myPrint(string myString, int newLineChecker);

        /// Funktion, um zu überprüfen, ob das Argument astyle-path angegeben wurde.
        ///
        /// Diese Funktion überprüft, ob beim aufrufen der .exe datei das Argument --astyle-path angegeben wurde.
        ///@returns bool
        /// \n **Beispiel Anwendung:**
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
        /// if(isSetastylepath())
        /// {
        ///     cout << "astyle-path wurde übergeben!" << endl;
        /// }
        ///
        /// OUTPUT:
        ///
        /// Das i
        /// st ei
        /// n Tes
        /// t für
        /// sign-
        /// per-l
        /// ine
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~
        ///@author Jacob
    public:
        bool isSetastylepath();
        /// Funktion, um auf das zusätzliche Argument von astyle-path zuzugreifen
        ///
        /// Diese Funktion gibt das Argument zurück, das als zusätzliches Argument zu Astyle-path angegeben wurde
        ///@returns string
        /// \n **Beispiel Anwendung:**
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
        /// cout << getValueOfastylepath << endl;
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~
        ///@author Jacob
    public:
        string getValueOfastylepath();
        /// Funktion, um den Hilfetext auszugeben
        ///
        /// Diese Funktion gibt den Hilfetext aus
        ///@returns void
        /// \n **Beispiel Anwendung:**
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
        /// printHelp()
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~
        ///@author Jacob
    protected:
        virtual void printHelp(const int signPerLine);
        /// Funktion, um zu überprüfen, ob das Argument only-if-newer angegeben wurde.
        ///
        /// Diese Funktion überprüft, ob beim aufrufen der .exe datei das Argument --astyle-path angegeben wurde.
        ///@returns bool
        /// \n **Beispiel Anwendung:**
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
        /// if(isSetonlyifnewer())
        /// {
        ///     cout << "only-if-newer wurde übergeben!" << endl;
        /// }
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~
        ///@author Jacob
    public:
        bool isSetonlyifnewer();
        /// Funktion, um zu überprüfen, ob das Argument no-format angegeben wurde.
        ///
        /// Diese Funktion überprüft, ob beim aufrufen der .exe datei das Argument --no-format angegeben wurde.
        ///@returns bool
        /// \n **Beispiel Anwendung:**
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
        /// if(isSetnoformat())
        /// {
        ///     cout << "no-format wurde übergeben!" << endl;
        /// }
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~
        ///@author Jacob
    public:
        bool isSetnoformat();
        /// Funktion, um zu überprüfen, ob das Argument out-path angegeben wurde.
        ///
        /// Diese Funktion überprüft, ob beim aufrufen der .exe datei das Argument --out-path angegeben wurde.
        ///@returns bool
        /// \n **Beispiel Anwendung:**
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
        /// if(isSetoutpath())
        /// {
        ///     cout << "out-path wurde übergeben!" << endl;
        /// }
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~
        ///@author Jacob
    public:
        bool isSetoutpath();
        /// Funktion, um auf das zusätzliche Argument von out-path zuzugreifen
        ///
        /// Diese Funktion gibt das Argument zurück, das als zusätzliches Argument zu Astyle-path angegeben wurde
        ///@returns string
        /// \n **Beispiel Anwendung:**
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
        /// cout << getValueOfoutpath << endl;
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~
        ///@author Jacob
    public:
        string getValueOfoutpath();
        /// Funktion, um zu überprüfen, ob das Argument parse-only angegeben wurde.
        ///
        /// Diese Funktion überprüft, ob beim aufrufen der .exe datei das Argument --parse-only angegeben wurde.
        ///@returns bool
        /// \n **Beispiel Anwendung:**
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
        /// if(isSetparseonly())
        /// {
        ///     cout << "parse-only wurde übergeben!" << endl;
        /// }
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~
        ///@author Jacob
    public:
        bool isSetparseonly();
        /// Funktion, um auf das zusätzliche Argument von parse-only zuzugreifen
        ///
        /// Diese Funktion gibt das Argument zurück, das als zusätzliches Argument zu parse-only angegeben wurde
        ///@returns bool
        /// \n **Beispiel Anwendung:**
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
        /// cout << getValueOfparseonly << endl;
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~
        ///@author Jacob
    public:
        bool getValueOfparseonly();
        /// Funktion, um auf das zusätzliche Argument von sign-per-line zuzugreifen
        ///
        /// Diese Funktion gibt das Argument zurück, das als zusätzliches Argument zu sign-per-line angegeben wurde
        ///@returns bool
        /// \n **Beispiel Anwendung:**
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
        /// cout << getValueOfsignperline << endl;
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~
        ///@author Jacob
    public:
        bool isSetsignperline();
        /// Funktion, um auf das zusätzliche Argument von sign-per-line zuzugreifen
        ///
        /// Diese Funktion gibt das Argument zurück, das als zusätzliches Argument zu sign-per-line angegeben wurde
        ///@returns int
        /// \n **Beispiel Anwendung:**
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
        /// cout << getValueOfsignperline << endl;
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~
        ///@author Jacob
    public:
        int getValueOfsignperline();
        /// Funktion, um zu überprüfen, ob das Argument version angegeben wurde.
        ///
        /// Diese Funktion überprüft, ob beim aufrufen der .exe datei das Argument --version angegeben wurde.
        ///@returns bool
        /// \n **Beispiel Anwendung:**
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
        /// if(isSetversion())
        /// {
        ///     cout << "version wurde übergeben!" << endl;
        /// }
        /// ~~~~~~~~~~~~~~~~~~~~~~~~~
        ///@author Jacob
    public:
        bool isSetversion();
        /// Externe Methode, kann in der exampleMain überschrieben Werden
        ///@author Jacob
    protected:
        virtual void ParseXML(bool b) = 0;
        /// Externe Methode, kann in der exampleMain überschrieben Werden
        ///@author Jacob
    protected:
        virtual void printVersion(int a) = 0;
        /// Funktion, um auf unbekannte Argumente reagieren zu können.
        ///
        /// Diese Funktion wird aufgerufen, wenn ein unbekanntes Argument erkannt wurde.
        ///@returns void
        ///@author Jacob
        virtual void unknownOption(const string &unknown_option);
        /// Funktion, um auf übergebene Argumente reagieren zu können.
        ///
        /// Diese Funktion wird aufgerufen, wenn die main() ausgeführt wird.
        ///@returns void
        ///@author Jacob
    public:
        void parseOptions(int argc, char *argv[]);
    };
}
#endif