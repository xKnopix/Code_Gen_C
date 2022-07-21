//Author: Michael Hornstein

#include "xml_parser.h"

xml_parser::GetOptSetup xml_parser::GetDataStrctFromXML(std::string filename){

    xml_parser::GetOptSetup data;

    DOMDocument* doc = GetDomDocument(filename);
    DOMElement*  rootNode = doc->getDocumentElement();

    //Get sign perline
    DOMNamedNodeMap *AttrMap = rootNode->getAttributes();
    data.signPerLine = toCh(AttrMap->item(0)->getTextContent());

    DOMNodeList* Author = doc->getElementsByTagName(toXMLCh("Author")); //Alle Nodes die Author heißen
    DOMNodeList* HeaderFileName = doc->getElementsByTagName(toXMLCh("HeaderFileName")); //Alle Nodes die HeaderFileName heißen
    DOMNodeList* SourceFileName = doc->getElementsByTagName(toXMLCh("SourceFileName")); //Alle Nodes die SourceFileName heißen
    DOMNodeList* NameSpace = doc->getElementsByTagName(toXMLCh("NameSpace")); //Alle Nodes die NameSpace heißen
    DOMNodeList* ClassName = doc->getElementsByTagName(toXMLCh("ClassName")); //Alle Nodes die ClassName heißen
    DOMNodeList* OverAllDescription = doc->getElementsByTagName(toXMLCh("OverAllDescription")); //Alle Nodes die OverAllDescription heißen
    DOMNodeList* SampleUsage = doc->getElementsByTagName(toXMLCh("SampleUsage")); //Alle Nodes die SampleUsage heißen
    DOMNodeList* Options = doc->getElementsByTagName(toXMLCh("Options")); //Alle Nodes die Options heißen

    DOMNodeList* Blocks = doc->getElementsByTagName(toXMLCh("Block")); //Alle Nodes die Options heißen
    DOMNodeList* Samples = doc->getElementsByTagName(toXMLCh("Sample")); //Alle Nodes die Options heißen
    DOMNodeList* Optionss = doc->getElementsByTagName(toXMLCh("Option")); //Alle Nodes die Options heißen

    data.author.mail = getAttriburte(Author->item(0), "Mail");
    data.author.phone = getAttriburte(Author->item(0), "Phone");
    data.author.name = getAttriburte(Author->item(0), "Name");

    data.headerFileName.content = toCh(HeaderFileName->item(0)->getTextContent());
    data.sourceFileName.content = toCh(SourceFileName->item(0)->getTextContent());

    data.nameSpace.content = toCh(NameSpace->item(0)->getTextContent());
    data.className.content = toCh(ClassName->item(0)->getTextContent());

    for(int i = 0; i < Blocks->getLength(); i++){
        xml_parser::Block b;
        b.content = toCh(Blocks->item(i)->getTextContent());
        data.overAllDescription.addBlock(b); 
    }

    for(int i = 0; i < Samples->getLength(); i++){
        xml_parser::Sample s;
        s.content = toCh(Samples->item(i)->getTextContent());
        data.sampleUsage.addSample(s);
    }

    for(int i = 0; i < Optionss->getLength(); i++){
        xml_parser::Option o;

        o.connectToInternalMethod = getAttriburte(Optionss->item(i), "ConnectToInternalMethod");
        o.description = getAttriburte(Optionss->item(i), "Description");
        o.exclusion = getAttriburte(Optionss->item(i), "Exclusion");
        o.hasArguments = getAttriburte(Optionss->item(i), "HasArguments");
        o.interface = getAttriburte(Optionss->item(i), "Interface");
        o.longOpt = getAttriburte(Optionss->item(i), "LongOpt");
        o.ref = getAttriburte(Optionss->item(i), "Ref");
        o.shortOpt = getAttriburte(Optionss->item(i), "ShortOpt");
        o.connectToExternalMethod =getAttriburte(Optionss->item(i), "ConnectToExternalMethod"); 
        o.convertTo = getAttriburte(Optionss->item(i), "ConvertTo");
        o.defaultValue = getAttriburte(Optionss->item(i), "DefaultValue");
        data.options.addOption(o);
        
    }
    return data;
}

//Helperfunktion
string xml_parser::getAttriburte(DOMNode* Node, string search) {
	string ret;
    
        if(Node->hasAttributes()){ //Schaue ob Author von (i) Attribute hat wie z.B Name, Email, Phone
            DOMNamedNodeMap *AttrMap = Node->getAttributes(); // Wenn ja erstelle einen Map von diesen Attributen
            
            for ( XMLSize_t j=0; j<AttrMap->getLength(); j++) { // gehe durch diese Map mit For loop durch
                
                string nodeName = toCh(AttrMap->item(j)->getNodeName());// attribut von xmlchar zu String convertieren um vergleiche zu können 
                if(nodeName == search){ //Vergleiche ob Attibut mail heißt
                    ret = toCh(AttrMap->item(j)->getTextContent()); // schreibe den content von Attribut Mail in a.mail
                }
            }
        }else{
            cout << "Es gint keine Attribute" << endl;
        }
        return ret;
}

DOMDocument* xml_parser::GetDomDocument(std::string xmlName){
    try {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& ec) {
        cout << "Error during initialization!" << endl;
    }

    /*
     * gValScheme = XercesDOMParser::Val_Never;
     * gValScheme = XercesDOMParser::Val_Auto;
     * gValScheme = XercesDOMParser::Val_Always;
     */

    XercesDOMParser* parser = new XercesDOMParser();
    parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setDoNamespaces(true);    // optional

    /*
     *  parser->setDoSchema(false);
     *  parser->setHandleMultipleImports (true);
     *  parser->setValidationSchemaFullChecking(true);
     *  parser->setCreateEntityReferenceNodes(false);
     */

    ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
    parser->setErrorHandler(errHandler);

    
    try{
        parser->parse(xmlName.c_str()); // Methode akkzeptiert nur const char
        DOMDocument* doc = parser->adoptDocument();
        return doc;
    }
    catch (const DOMException& ec) {
        cout << "DOMException : " << endl;
    }
    catch ( const SAXParseException &ec ) {
        std::cout << "SAXParseException during Parsing\n";
    }
    catch (...) {
        std::cout << "Unexpected Exception During Parsing\n" ;
    }
    finally:{
        delete parser;
        delete errHandler;
    }



}
