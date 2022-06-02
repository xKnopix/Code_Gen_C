#include "xml_parser.h"

int main() {
    xml_parser x;

    xml_parser::GetOptSetup data = x.GetDataStrctFromXML("Example.xml");

    cout << data.options.option[1].description << endl;
    return 0;
}
