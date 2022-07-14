#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <iostream>
#include <vector>
#include "pugixml-1.12/src/pugixml.hpp"

using namespace std;
using namespace pugi;

class xml_parser{
public:
    struct Author {
        std::string name;
        std::string phone;
        std::string mail;
    };

    struct HeaderFileName {
        std::string content;
    };

    struct SourceFileName {
        std::string content;
    };

    struct NameSpace {
        std::string content;
    };

    struct ClassName {
        std::string content;
    };

    struct Block{
        std::string content;
    };

    struct OverAllDescription {
        std::vector<Block> block;
        virtual void addBlock(const Block &b){ block.push_back(b);}
    };

    struct Sample{
        std::string content;
    };

    struct SampleUsage{
        std::vector<Sample> sample;
        virtual void addSample(Sample const &s){ sample.push_back(s);}
    };

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

    struct Options{
        std::vector<Option> option;
        virtual void addOption(Option const &o){ option.push_back(o);}
    };
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

    GetOptSetup GetDataStrctFromXML(std::string filename);
private:
    vector<xml_node> getChildNodes(xml_node parentNode, pugi::char_t* child_Name);
};
#endif