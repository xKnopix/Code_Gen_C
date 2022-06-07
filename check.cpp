#include "check.h"

int check::check_data(xml_parser::GetOptSetup data){
    int status = 1;
    status = check_author(data.author);
    status = check_headerfile(data.headerFileName);
    status = check_sourcefile(data.sourceFileName);
    status = check_namespace(data.nameSpace);
    status = check_classname(data.className);
    check_overall_description(data.overAllDescription);
    /*
    check_sample_usage(data.sampleUsage);
    check_options(data.options);
    */
   return status;
}

int check::check_author(xml_parser::Author author){
    int status = 1;
    if(author.name.empty()){//überprufen ob ein name angegeben wurde
        cout << "Es muss ein Author angegeben werden" << endl;
        status = -1;
    }

    if(author.mail.empty()){//überprüft ob Mail angegeben wurde
        cout << "Es muss mindestens eine Email angegeben werden" << endl;
        status = -1;
    }else{
        if (author.mail.find('@') == std::string::npos){//@ wurde nicht gefunden
            cout << "Es wurde keine Gueltige Email angegeben" << endl;
            status -1;
        }
    }

    if(author.phone.empty()){
        cout << "Es wurde keine Telefonnummer angegeben(optional)" << endl;
    }
    return status;
}
int check::check_headerfile(xml_parser::HeaderFileName header){
    int status = 1;
    if(header.content.empty()){
        cout << "Es wurde kein Name fuer eine Headerfile angegeben" << endl;
        status = -1;
    }else if(header.content.find(".h") == std::string::npos){//.h wurde nicht gefunden
        cout << "Die Headerdatei muss mit \".h\" enden" << endl;
        status -1;
        }
    return status;
}
int check::check_sourcefile(xml_parser::SourceFileName source){
    int status = 1;
    if(source.content.empty()){
        cout << "Es wurde kein Name fuer eine Sourcefile angegeben, deswegen wird keine Sourcefile generiert (optional)" << endl;
        status = 1;
    }else if(source.content.find(".cpp") == std::string::npos){//.h wurde nicht gefunden
        cout << "Die Sourcedatei muss mit \".cpp\" enden" << endl;
        status -1;
        }
    return status;
}
int check::check_namespace(xml_parser::NameSpace namesp){
    int status = 1;
    if(namesp.content.empty()){
        cout << "Es wurde kein Namespace angegeben (optional)" << endl;
        status = 1;
        }
        return status;
}
int check::check_classname(xml_parser::ClassName cname){
        int status = 1;
    if(cname.content.empty()){
        cout << "Es wurde kein Klassenname angegeben" << endl;
        status = -1;
    }
    return status;
}
int check::check_overall_description(xml_parser::OverAllDescription ovdes){
    cout << ovdes.block.size() << endl;
}
/*
int check::check_block(xml_parser::Block){}
int check::check_sample_usage(xml_parser::SampleUsage){}
int check::check_sample(xml_parser::SampleUsage){}
int check::check_options(xml_parser::Options){}
int check::check_option(xml_parser::Option){}
*/
