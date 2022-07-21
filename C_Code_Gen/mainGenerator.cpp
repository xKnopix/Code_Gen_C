//Author: Michael Hornstein

#include "mainGenerator.h"

mainGenerator::mainGenerator(xml_parser::GetOptSetup data){
    
    includes(data.headerFileName);
    useNameSpace(data.nameSpace);
    genInheriteClass(data.options, data.className);
    genMain();

    std::ofstream MyFile("exampleMain.cpp");
    MyFile << this->output;
    MyFile.close();
}

void mainGenerator::useNameSpace(xml_parser::NameSpace namesp){
    this->output.append("using namespace std;\n");
    this->output.append("using namespace ");
    this->output.append(namesp.content);
    this->output.append(";\n\n");
}

void mainGenerator::genMain(){
    
    this->output.append("int main(int argc, char *argv[]){\n\n");
    this->output.append("\tKlasse k;\n");
    this->output.append("\tk.parseOptions(argc, argv);\n");
    this->output.append("}");
}

void mainGenerator::genInheriteClass(xml_parser::Options options, xml_parser::ClassName classN){

    vector<std::string> s;
    vector<std::string> c;

    for(int i = 0; i<options.option.size(); i++){
        if(!options.option[i].connectToExternalMethod.empty()){// wenn eine externe Methde angegeben wurde
            s.push_back(options.option[i].connectToExternalMethod); 
            c.push_back(options.option[i].convertTo);
        }
    }

    if(s.size() >0){
        
        this->output.append("///Diese Klasse erbt von");
        this->output.append(classN.content);
        this->output.append(" , hier können die Externen Methoden ueberschrieben werden\n");

        this->output.append("class Klasse : public ");
        this->output.append(classN.content);
        this->output.append("{\n\n");
        this->output.append("public:\n\n");

        for(int i = 0; i<s.size(); i++){
            this->output.append("void ");
            this->output.append(s[i]);
            this->output.append("(");
            if(!c.empty()){//Wenn etwas in coverTo steht dann...
                if(!c[i].compare("Integer") || !c[i].compare("integer")){
                    this->output.append("int a");
                }else if(!c[i].compare("Bool") || !c[i].compare("bool")){
                    this->output.append("bool b");
                }else if(!c[i].compare("String") || !c[i].compare("string")){
                    this->output.append("string s");
                }
            }
            this->output.append("){");
            this->output.append("///Die Methode wird vererbt und soll ueberschrieben werden");
            this->output.append("\n\tcout << \"Example implementation of external Method\" << endl;\n}\n\n");
        }
        this->output.append("};\n\n");
    }

}

void mainGenerator::includes(xml_parser::HeaderFileName header){
    this->output.append("#include<iostream>\n");
    this->output.append("#include\"");    
    this->output.append(header.content); 
    this->output.append("\"\n\n"); 
}
