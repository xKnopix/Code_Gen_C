//Author: Michael Hornstein

#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <iostream>
#include <vector>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include "xmlCh.h"

using namespace std;
using namespace xercesc;

///Diese Klasse ist da um eine XML einzulesen und in dem Struct GetOptSetup zu speichern
class xml_parser{
public:
    /// Dieses Struct ist für die Speicherung des Autoren zusändig
    /// @param name
    /// @param phone
    /// @param mail
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include "xml_parser.h"
    ///
    /// xml_parser::Author Author;
    /// author.name = "Max";
    /// author.phone = "0152...";
    /// author.maile = "max.mustermann@fmail.com";
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Michael 
    struct Author {
        std::string name;
        std::string phone;
        std::string mail;
    };
    /// Dieses Struct ist für die Speicherung des Headerfilename zusändig
    /// @param content 
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include "xml_parser.h"
    ///
    /// xml_parser::HeaderFileName headerFileName;
    /// headerFileName.content = "test.h";
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Michael
    struct HeaderFileName {
        std::string content;
    };

    /// Dieses Struct ist für die Speicherung des SourceFilename zusändig
    /// @param content 
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include "xml_parser.h"
    ///
    /// xml_parser::SourceFileName sourceFileName;
    /// SourceFileName.content = "test.cpp";
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Michael
    struct SourceFileName {
        std::string content;
    };

    /// Dieses Struct ist für die Speicherung des NameSpace zusändig
    /// @param content 
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include "xml_parser.h"
    ///
    /// xml_parser::NameSpace nameSpace;
    /// nameSpace.content = "test";
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Michael
    struct NameSpace {
        std::string content;
    };

    /// Dieses Struct ist für die Speicherung des ClassName zusändig
    /// @param content 
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include "xml_parser.h"
    ///
    /// xml_parser::ClassName className;
    /// className.content = "testClass";
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Michael
    struct ClassName {
        std::string content;
    };

    /// Dieses Struct ist für die Speicherung des Blocks zusändig
    /// @param content 
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include "xml_parser.h"
    ///
    /// xml_parser::Block block;
    /// block.content = "test Block...";
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Michael
    struct Block{
        std::string content;
    };

    /// Dieses Struct ist für die Speicherung von Blöcken zusändig
    /// @param vector<Block> 
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include "xml_parser.h"
    ///
    /// xml_parser::OverAllDescription overAllDescription;
    /// OverAllDescription.addBlock(xml_parser::Block b);
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Michael
    struct OverAllDescription {
        std::vector<Block> block;
        virtual void addBlock(const Block &b){ block.push_back(b);}
    };

    /// Dieses Struct ist für die Speicherung von einem Sample zusändig
    /// @param content 
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include "xml_parser.h"
    ///
    /// xml_parser::Sample sample;
    /// sample.content = "test Sample...";
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Michael
    struct Sample{
        std::string content;
    };

    /// Dieses Struct ist für die Speicherung von Samples zusändig
    /// @param vector<Sample> 
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include "xml_parser.h"
    ///
    /// xml_parser::SampleUsage sampleUsage;
    /// sampleUsage.addBlock(xml_parser::Sample s);
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Michael
    struct SampleUsage{
        std::vector<Sample> sample;
        virtual void addSample(Sample const &s){ sample.push_back(s);}
    };
    /// Dieses Struct ist für die Speicherung von einer Option zusändig
    /// @param ref 
    /// @param shortOpt
    /// @param longOpt
    /// @param exclusion
    /// @param connectToInternalMethod
    /// @param description
    /// @param interface
    /// @param hasArguments
    /// @param convertTo
    /// @param defaultValue
    /// @param connectToExternalMethod
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include "xml_parser.h"
    ///
    /// xml_parser::Option option;
    /// option.ref = "test ref";
    /// option.shortOpt = "r";
    /// option.longOpt = "ref";
    /// option.exclusion = "1,2";
    /// option.connectToInternalMethod = "printref";
    /// option.description = "description";
    /// option.interface = "interface";
    /// option.hasArguments = "args";
    /// option.convertTo = "Integer";
    /// option.defaultValue = "1";
    /// option.connectToExternalMethod = "print";
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Michael
    struct Option{
        std::string ref;
        std::string shortOpt;
        std::string longOpt;
        std::string exclusion;
        std::string connectToInternalMethod;
        std::string description;
        std::string interface;
        std::string hasArguments;
        std::string convertTo;
        std::string defaultValue;
        std::string connectToExternalMethod;
    };

    /// Dieses Struct ist für die Speicherung von options zusändig
    /// @param vector<Option> 
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include "xml_parser.h"
    ///
    /// xml_parser::Options Options;
    /// Options.addOption(xml_parser::option o);
    /// Options.printOptions();
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Michael
    struct Options{
        std::vector<Option> option;
        virtual void addOption(Option const &o){ option.push_back(o);}
        virtual void printOpions(){for(int i = 0; i< option.size(); i++){cout << "option " << i << option[i].connectToExternalMethod << ", " << option[i].connectToInternalMethod << ", " << option[i].convertTo << ", " << option[i].defaultValue
                                                                                << ", " << option[i].description << ", " << option[i].exclusion << ", " << option[i].hasArguments << ", " << option[i].interface << ", " << option[i].longOpt << ", "
                                                                                << option[i].ref << ", " << option[i].shortOpt << endl;}}
    };
    /// Dieses Struct ist für die Speicherung von allen anderen Structs zuständig
    /// @param signPerLine
    /// @param author  
    /// @param headerFileName
    /// @param sourceFileName
    /// @param nameSpace
    /// @param className
    /// @param overAllDescription
    /// @param sampleUsage
    /// @param options
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include "xml_parser.h"
    ///
    /// xml_parser::GetOptSetup data;
    /// xml_parser::Option o;
    ///
    /// data.options.addOption(o);
    /// data.options[0].connectToExternalMethod = "printhelp";
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Michael

    struct GetOptSetup {
        string signPerLine = "79";
        Author author;
        HeaderFileName headerFileName;
        SourceFileName sourceFileName;
        NameSpace nameSpace;
        ClassName className;
        OverAllDescription overAllDescription;
        SampleUsage sampleUsage;
        Options options;
    };
    ///Diese Methode ist dafür zuständig eine XML auszulesen und der inhalt in das Struct GetOptSetup zu schreieben
    /// @param stirng filename
    /// @return GetOptSetup
    /// \n **Beispiel Anwendung:**
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~.cpp
    /// #include "xml_parser.h"
    ///
    /// xml_parser::GetOptSetup data;
    /// 
    /// xml_parser x;
    /// xml_parser::GetOptSetup data = x.GetDataStrctFromXML("Example.xml");
    ///
    /// cout << data.options.printOptions() << endl;
    /// ~~~~~~~~~~~~~~~~~~~~~~~~~
    ///@author Michael
    GetOptSetup GetDataStrctFromXML(std::string filename);
private:
    DOMDocument* GetDomDocument(std::string xmlName);
    string getAttriburte(DOMNode* Node, string search);
};
#endif
