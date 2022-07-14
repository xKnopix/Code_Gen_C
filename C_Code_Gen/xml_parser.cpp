#include "xml_parser.h"

xml_parser::GetOptSetup xml_parser::GetDataStrctFromXML(std::string filename){
    xml_document doc; //crates a xmldoc;

    xml_parser::GetOptSetup data;

    xml_parse_result result = doc.load_file(filename.c_str()); //convert string to const char*
    cout << "XML File load result: " << result.description() << endl;
    xml_node GetOptSetup = doc.child("GetOptSetup");//config is new parent node
    data.signPerLine = GetOptSetup.attribute("SignPerLine").value();

    xml_node Author = GetOptSetup.child("Author");
    xml_node HeaderFileName = GetOptSetup.child("HeaderFileName");
    xml_node SourceFileName = GetOptSetup.child("SourceFileName");
    xml_node NameSpace = GetOptSetup.child("NameSpace");
    xml_node ClassName = GetOptSetup.child("ClassName");
    xml_node OverAllDescription = GetOptSetup.child("OverAllDescription");
    xml_node SampleUsage = GetOptSetup.child("SampleUsage");
    xml_node Options = GetOptSetup.child("Options");

    vector<xml_node> Blocks = getChildNodes(OverAllDescription, (pugi::char_t*)"Block");
    vector<xml_node> Samples = getChildNodes(SampleUsage, (pugi::char_t*)"Sample");
    vector<xml_node> Optionss = getChildNodes(Options, (pugi::char_t*)"Option");

    data.signPerLine = GetOptSetup.attribute("SignPerLine").value();

    data.author.mail = Author.attribute("Mail").value();
    data.author.phone = Author.attribute("Phone").value();
    data.author.name = Author.attribute("Name").value();

    data.headerFileName.content = HeaderFileName.child_value();
    data.sourceFileName.content = SourceFileName.child_value();

    data.nameSpace.content = NameSpace.child_value();

    data.className.content = ClassName.child_value();

    for(int i = 0; i < Blocks.size(); i++){
        xml_parser::Block b;
        b.content = Blocks[i].child_value();
        data.overAllDescription.addBlock(b); 
    }

    for(int i = 0; i < Samples.size(); i++){
        xml_parser::Sample s;
        s.content = Samples[i].child_value();
        data.sampleUsage.addSample(s);
    }

    for(int i = 0; i < Optionss.size(); i++){
        xml_parser::Option o;
        o.connectToInternalMethod = Optionss[i].attribute("ConnectToInternalMethod").value();
        o.description = Optionss[i].attribute("Description").value();
        o.exclusion = Optionss[i].attribute("Exclusion").value();
        o.hasArguments = Optionss[i].attribute("HasArguments").value();
        o.interface = Optionss[i].attribute("Interface").value();
        o.longOpt = Optionss[i].attribute("LongOpt").value();
        o.ref = Optionss[i].attribute("Ref").value();
        o.shortOpt = Optionss[i].attribute("ShortOpt").value();
        o.connectToExternalMethod = Optionss[i].attribute("ConnectToExternalMethod").value();
        o.convertTo = Optionss[i].attribute("ConvertTo").value();
        o.defaultValue = Optionss[i].attribute("DefaultValue").value();
        data.options.addOption(o);
    }  


    
    cout<< data.options.option[1].shortOpt  << endl;
    return data;
}

//Helperfunktion
vector<xml_node> xml_parser::getChildNodes(xml_node parentNode, pugi::char_t* childName) {
	
	vector<xml_node> childNodes;

	for (xml_node child = parentNode.child(childName); child; child = child.next_sibling(childName)) {
		childNodes.push_back(child);
		//cout << child.attribute("student_type").value() << endl;
	}
	return childNodes;
}