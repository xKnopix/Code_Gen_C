//Author: Michael Hornstein

#ifndef CHECK_H
#define CHECK_H

#include "xml_parser.h"

/// Diese Klasse ist da um zu überprüfen ob in der XML alles angegeben wurde und die Daten zu sortieren
class check
{
public:
    ///Diese Methode wird aufgerufen um ein datenOpjekt (des Typs GetOptSetup) auf vollständigkeit zu überpüfen
    ///@param data daten Objekt des Typs xml_parser::GetOptSetup
    ///@return 1 wenn alles gut ist und -1 wenn etwas fehlt
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include "check.h"
    ///
    /// check c;
    /// c.check_data(data);
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Michael  
    int check_data(xml_parser::GetOptSetup data);
    ///Diese Methode wird aufgerufen um ein datenOpjekt (des Typs GetOptSetup) nach dem Alphabet zu Sortieren
    ///Es wird hier bei nach shortOpt sortiert und wenn es kein shortOpt gibt, nach LongOpt
    ///@param xml_parser::GetOptSetup data daten Objekt des Typs xml_parser::GetOptSetup
    ///@return xml_parser::GetOptSetup data in sortierter Reienfolge 
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    ///#include "check.h"
    ///
    /// check c;
    /// xml_parser::GetOptSetup data = c.sortData(data);
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Michael 
    xml_parser::GetOptSetup sortData(xml_parser::GetOptSetup data);
private:
    int check_author(xml_parser::Author);
    int check_headerfile(xml_parser::HeaderFileName);
    int check_sourcefile(xml_parser::SourceFileName);
    int check_namespace(xml_parser::NameSpace);
    int check_classname(xml_parser::ClassName);
    int check_overall_description(xml_parser::OverAllDescription);
    int check_block(xml_parser::Block);
    int check_sample_usage(xml_parser::SampleUsage);
    int check_sample(xml_parser::Sample);
    int check_options(xml_parser::Options);
    int check_option(xml_parser::Option, int i);
    int compStringS1SmalerS2(string s1, string s2);
    
};

#endif
