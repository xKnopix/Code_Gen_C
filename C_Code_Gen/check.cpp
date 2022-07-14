#include "check.h"

int check::check_data(xml_parser::GetOptSetup data){
    int status = 1;
    status = check_author(data.author);
    status = check_headerfile(data.headerFileName);
    status = check_sourcefile(data.sourceFileName);
    status = check_namespace(data.nameSpace);
    status = check_classname(data.className);
    status = check_overall_description(data.overAllDescription);
    status = check_sample_usage(data.sampleUsage);
    status = check_options(data.options);
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
    if (ovdes.block.size() == 0 || ovdes.block[0].content.empty()){
        cout << "Es wurde keine Beschreibung angegeben (optional) Bsp:<OverAllDescription><Block>\"\"</Block></OverAllDescription>" << endl;
    }
    for (int i = 0; i < ovdes.block.size(); i++){
        check_block(ovdes.block[i]);
    }
    return 1;
}
int check::check_block(xml_parser::Block bl){
    if(bl.content.empty()){
        cout << "Es wurde ein leerer <Block></Block> angegeben dieser sollte befuellt werden(optional)" << endl;
    }
    return 1;
}
int check::check_sample_usage(xml_parser::SampleUsage sample){
    if (sample.sample.size() == 0 || sample.sample[0].content.empty()){
        cout << "Es wurde kein Beispiel angegeben (optional) Bsp:<SampleUsage><Sample>\"\"</Sample></SampleUsage>" << endl;
    }
    for (int i = 0; i < sample.sample.size(); i++){
        check_sample(sample.sample[i]);
    }
    return 1;
}
int check::check_sample(xml_parser::Sample sp){
    if(sp.content.empty()){
        cout << "Es wurde ein leerer <Sample></Sample> Tag angegeben dieser sollte befuellt werden(optional)" << endl;
    }  
    return 1;  
}
int check::check_options(xml_parser::Options opti){
    int status = 1;
    if(opti.option.size() == 0){
        cout << "Es wurde keine Option zum Parsen hinterlegt!" << endl;
        return -1;
    }
    for (int i = 0; i < opti.option.size(); i++){
        int s = check_option(opti.option[i], i);
        if(!s){
            status = -1;
        }
    }
    return status;
    
}
int check::check_option(xml_parser::Option opt, int i){
    if(opt.shortOpt.empty() && opt.longOpt.empty()){
        cout << "In Option " << i+1 << " muss das Argument \"ShortOpt=\" oder \"LongOpt=\" gesetzt sein" << endl;
        return -1;
    }
    return 1;
}
