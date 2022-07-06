#include "xml_parser.h"

xml_parser::GetOptSetup xml_parser::GetDataStrctFromXML(std::string filename){
    DOMDocument* doc = GetDomDocument(filename);
    xml_parser::GetOptSetup data = xml_parser::GetOptSetup();
    data = ParseDOMToDataStrct(doc);
    doc->release();
    XMLPlatformUtils::Terminate();
    return data;
}

xml_parser::GetOptSetup xml_parser::ParseDOMToDataStrct(DOMDocument* doc){
    xml_parser::GetOptSetup data = xml_parser::GetOptSetup();
    DOMElement*  rootNode = doc->getDocumentElement();
    
    //Get signPerLine
    DOMNamedNodeMap *AttrMap = rootNode->getAttributes();
    data.signPerLine = toCh(AttrMap->item(0)->getTextContent());
    data.author = GetAuthor(doc);
    data.headerFileName.content = toCh(doc->getElementsByTagName(toXMLCh("HeaderFileName"))->item(0)->getTextContent());
    data.sourceFileName.content = toCh(doc->getElementsByTagName(toXMLCh("SourceFileName"))->item(0)->getTextContent());
    data.nameSpace.content = toCh(doc->getElementsByTagName(toXMLCh("NameSpace"))->item(0)->getTextContent());
    data.className.content = toCh(doc->getElementsByTagName(toXMLCh("ClassName"))->item(0)->getTextContent());
    data.overAllDescription = GetOverAllDescription(doc);
    data.sampleUsage = GetSampleUsage(doc);
    data.options = GetOptions(doc);

    return data;
}

/*
 * std::string ref;
    std::string shortOpt;
    std::string longOpt;
    std::string exclusion;
    std::string connectToInternalMethod;
    std::string description;
    std::string interface;
    std::string hasArguments;
 */

xml_parser::Options xml_parser::GetOptions(DOMDocument* doc)
{
    xml_parser::Options o = xml_parser::Options();

    DOMNodeList* optionList = doc->getElementsByTagName(toXMLCh("Option")); //Hole alle Nodes die "Author" heißen
    for ( XMLSize_t i = 0; i < optionList->getLength(); i++ ) { //gehe durch diese liste durch
        if(optionList->item(i)->hasAttributes()){ //Schaue ob Author von (i) Attribute hat wie z.B Name, Email, Phone
            DOMNamedNodeMap *AttrMap = optionList->item(i)->getAttributes(); // Wenn ja erstelle einen Map von diesen Attributen

            xml_parser::Option option = xml_parser::Option();

            for ( XMLSize_t j=0; j<AttrMap->getLength(); j++) { // gehe durch diese Map mit For loop durch



                string nodeName = toCh(AttrMap->item(j)->getNodeName());// attribut von xmlchar zu String convertieren um vergleiche zu können

                if(nodeName == "Ref"){ //Vergleiche ob Attribut mail heißt
                    option.ref = toCh(AttrMap->item(j)->getTextContent()); // schreibe den content von Attribut Mail in a.mail
                }else if(nodeName == "ShortOpt"){
                    option.shortOpt = toCh(AttrMap->item(j)->getTextContent());
                }else if(nodeName == "LongOpt"){
                    option.longOpt = toCh(AttrMap->item(j)->getTextContent());
                }else if(nodeName == "Exclusion"){
                    option.exclusion = toCh(AttrMap->item(j)->getTextContent());
                }else if(nodeName == "ConnectToInternalMethod"){
                    option.connectToInternalMethod = toCh(AttrMap->item(j)->getTextContent());
                }else if(nodeName == "Description"){
                    option.description = toCh(AttrMap->item(j)->getTextContent());
                }else if(nodeName == "Interface"){
                    option.interface = toCh(AttrMap->item(j)->getTextContent());
                }else if(nodeName == "HasArguments"){
                    option.hasArguments = toCh(AttrMap->item(j)->getTextContent());
                }
            }
            o.addOption(option);
        }
    }
    return o;
}

xml_parser::SampleUsage xml_parser::GetSampleUsage(DOMDocument* doc)
{
    xml_parser::SampleUsage sA = xml_parser::SampleUsage();

    DOMNodeList* sampleUsageList = doc->getElementsByTagName(toXMLCh("Sample")); //Hole alle Nodes die "Author" heißen


    for ( XMLSize_t i=0;i<sampleUsageList->getLength(); i++)
    {
        //cout << "textCont: " << toCh(blockList->item(i)->getTextContent())<< endl;

        xml_parser::Sample sample = xml_parser::Sample();

        sample.content = toCh(sampleUsageList->item(i)->getTextContent());

        sA.addSample(sample);


    }

    return sA;
}




xml_parser::OverAllDescription xml_parser::GetOverAllDescription(DOMDocument* doc)
{
    xml_parser::OverAllDescription oA = xml_parser::OverAllDescription();

         //Passt nur, OverAllDescription das einzige element mit "Block"-Elementen ist, da alle BlockElemente hier geladen werden, aus der ganzen Datei
         DOMNodeList* blockList = doc->getElementsByTagName(toXMLCh("Block")); //Alle Nodes die Block heißen

         for ( XMLSize_t i=0;i<blockList->getLength(); i++)
         {
             //cout << "textCont: " << toCh(blockList->item(i)->getTextContent())<< endl;

             xml_parser::Block block = xml_parser::Block();

             block.content = toCh(blockList->item(i)->getTextContent());

             oA.addBlock(block);

         }


    return oA;




        /*for(XMLSize_t i = 0; i < blockList->getLength(); i++) //Alle Block_Elemente durchgehen
        {
            cout<<"2"<<endl;
            if(blockList->item(i)->hasAttributes())
            {
                cout<<"3"<<endl;
                DOMNamedNodeMap *AttrMap = blockList->item(i)->getAttributes();

                for(XMLSize_t j =0; j<AttrMap->getLength(); j++)
                {
                    cout<<"4"<<endl;
                    string blockText = toCh(AttrMap->item(j)->getTextContent());
                    cout << "TEST_TEXT" << blockText << endl;
                }

            }

        }*/

}

xml_parser::Author xml_parser::GetAuthor(DOMDocument* doc){
    xml_parser::Author a = xml_parser::Author();

    DOMNodeList* authorList = doc->getElementsByTagName(toXMLCh("Author")); //Hole alle Nodes die "Author" heißen
    for ( XMLSize_t i = 0; i < authorList->getLength(); i++ ) { //gehe durch diese liste durch
        if(authorList->item(i)->hasAttributes()){ //Schaue ob Author von (i) Attribute hat wie z.B Name, Email, Phone
            DOMNamedNodeMap *AttrMap = authorList->item(i)->getAttributes(); // Wenn ja erstelle einen Map von diesen Attributen
            
            for ( XMLSize_t j=0; j<AttrMap->getLength(); j++) { // gehe durch diese Map mit For loop durch
                
                string nodeName = toCh(AttrMap->item(j)->getNodeName());// attribut von xmlchar zu String convertieren um vergleiche zu können 
                if(nodeName == "Mail"){ //Vergleiche ob Attibut mail heißt
                    a.mail = toCh(AttrMap->item(j)->getTextContent()); // schreibe den content von Attribut Mail in a.mail
                }else if(nodeName == "Phone"){
                    a.phone = toCh(AttrMap->item(j)->getTextContent());
                }else if(nodeName == "Name"){
                    a.name = toCh(AttrMap->item(j)->getTextContent());
                }
            }
        }else{
            cout << "Es wurden keine Informationen zum Autor hinterlegt!" << endl;
        }
    }
    return a;
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
