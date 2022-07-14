#ifndef CHECK_H
#define CHECK_H

#include "xml_parser.h"

class check
{
public:
    int check_data(xml_parser::GetOptSetup data);
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
};

#endif
