//Author: Michael Hornstein

#include "check.h"

int check::check_data(xml_parser::GetOptSetup data)
{
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

xml_parser::GetOptSetup check::sortData(xml_parser::GetOptSetup data)///Sortiert die optionen Alphabetisch mit dem BubbleSort Algorithmus
{
    //Standart Bubblesort
    int i, j, pass = 0;
    xml_parser::Option temp;

    for (i = 0; i < data.options.option.size(); i++)
    {
        for (j = i + 1; j < data.options.option.size(); j++)
        {
            if(data.options.option[j].shortOpt.empty() && data.options.option[i].shortOpt.empty()){//beide short opt leer sind
                if(compStringS1SmalerS2(data.options.option[j].longOpt, data.options.option[i].longOpt))
                {
                    temp = data.options.option[i];
                    data.options.option[i] = data.options.option[j];
                    data.options.option[j] = temp;
                }
            }else if(!data.options.option[j].shortOpt.empty() && data.options.option[i].shortOpt.empty()){// Wenn j nicht leer ist und i leer
                if(compStringS1SmalerS2(data.options.option[j].shortOpt, data.options.option[i].longOpt))
                {
                    temp = data.options.option[i];
                    data.options.option[i] = data.options.option[j];
                    data.options.option[j] = temp;
                }
            }else if(data.options.option[j].shortOpt.empty() && !data.options.option[i].shortOpt.empty()){// Wenn i nicht leer ist und j leer
                if(compStringS1SmalerS2(data.options.option[j].longOpt, data.options.option[i].shortOpt))
                {
                    temp = data.options.option[i];
                    data.options.option[i] = data.options.option[j];
                    data.options.option[j] = temp;
                }
            }else{
                if(compStringS1SmalerS2(data.options.option[j].shortOpt, data.options.option[i].shortOpt))
                {
                    temp = data.options.option[i];
                    data.options.option[i] = data.options.option[j];
                    data.options.option[j] = temp;
                } 
            }
        }
        pass++;
    }

    return data;
}

int check::compStringS1SmalerS2(string s1, string s2)///um zwei Strings mit < vergleichen zukönnen (Hilfsfunktion)
{ // returns 1 if s1 is smaler than s2

    char c1 = s1.front();
    char c2 = s2.front();

    c1 = tolower(c1);
    c2 = tolower(c2);

    if (c1 < c2)
    {
        return 1;
    }

    return 0;
}

int check::check_author(xml_parser::Author author)///überpüft die Daten, welche zu dem Author gemacht worden sind und ob notwendige Daten Fehlen
{
    int status = 1;
    if (author.name.empty())
    { //überprufen ob ein name angegeben wurde
        cerr << "Es muss ein Author angegeben werden" << endl;
        status = -1;
    }

    if (author.mail.empty())
    { //überprüft ob Mail angegeben wurde
        cerr << "Es muss mindestens eine Email angegeben werden" << endl;
        status = -1;
    }
    else
    {
        if (author.mail.find('@') == std::string::npos)
        { //@ wurde nicht gefunden
            cerr << "Es wurde keine Gueltige Email angegeben" << endl;
            status - 1;
        }
    }

    if (author.phone.empty())
    {
        cerr << "Es wurde keine Telefonnummer angegeben(optional)" << endl;
    }
    return status;
}
int check::check_headerfile(xml_parser::HeaderFileName header)///überpüft die Daten, welche zu dem headerfile gemacht worden sind und ob notwendige Daten Fehlen
{
    int status = 1;
    if (header.content.empty())
    {
        cerr << "Es wurde kein Name fuer eine Headerfile angegeben" << endl;
        status = -1;
    }
    else if (header.content.find(".h") == std::string::npos)
    { //.h wurde nicht gefunden
        cerr << "Die Headerdatei muss mit \".h\" enden" << endl;
        status - 1;
    }
    return status;
}
int check::check_sourcefile(xml_parser::SourceFileName source)///überpüft die Daten, welche zu dem sourcefile gemacht worden sind und ob notwendige Daten Fehlen
{
    int status = 1;
    if (source.content.empty())
    {
        cerr << "Es wurde kein Name fuer eine Sourcefile angegeben, deswegen wird keine Sourcefile generiert (optional)" << endl;
        status = 1;
    }
    else if (source.content.find(".cpp") == std::string::npos)
    { //.h wurde nicht gefunden
        cerr << "Die Sourcedatei muss mit \".cpp\" enden" << endl;
        status - 1;
    }
    return status;
}
int check::check_namespace(xml_parser::NameSpace namesp)///überpüft die Daten, welche zu dem namespace gemacht worden sind und ob notwendige Daten Fehlen
{
    int status = 1;
    if (namesp.content.empty())
    {
        cerr << "Es wurde kein Namespace angegeben (optional)" << endl;
        status = 1;
    }
    return status;
}
int check::check_classname(xml_parser::ClassName cname)///überpüft die Daten, welche zu dem classname gemacht worden sind und ob notwendige Daten Fehlen
{
    int status = 1;
    if (cname.content.empty())
    {
        cerr << "Es wurde kein Klassenname angegeben" << endl;
        status = -1;
    }
    return status;
}
int check::check_overall_description(xml_parser::OverAllDescription ovdes)///überpüft die Daten, welche zu dem overall_description gemacht worden sind und ob notwendige Daten Fehlen
{
    if (ovdes.block.size() == 0 || ovdes.block[0].content.empty())
    {
        cerr << "Es wurde keine Beschreibung angegeben (optional) Bsp:<OverAllDescription><Block>\"\"</Block></OverAllDescription>" << endl;
    }
    for (int i = 0; i < ovdes.block.size(); i++)
    {
        check_block(ovdes.block[i]);
    }
    return 1;
}
int check::check_block(xml_parser::Block bl)///überpüft die Daten, welche zu dem block gemacht worden sind und ob notwendige Daten Fehlen
{
    if (bl.content.empty())
    {
        cerr << "Es wurde ein leerer <Block></Block> angegeben dieser sollte befuellt werden(optional)" << endl;
    }
    return 1;
}
int check::check_sample_usage(xml_parser::SampleUsage sample)///überpüft die Daten, welche zu dem sample_usage gemacht worden sind und ob notwendige Daten Fehlen
{
    if (sample.sample.size() == 0 || sample.sample[0].content.empty())
    {
        cerr << "Es wurde kein Beispiel angegeben (optional) Bsp:<SampleUsage><Sample>\"\"</Sample></SampleUsage>" << endl;
    }
    for (int i = 0; i < sample.sample.size(); i++)
    {
        check_sample(sample.sample[i]);
    }
    return 1;
}
int check::check_sample(xml_parser::Sample sp)///überpüft die Daten, welche zu dem sample gemacht worden sind und ob notwendige Daten Fehlen
{
    if (sp.content.empty())
    {
        cerr << "Es wurde ein leerer <Sample></Sample> Tag angegeben dieser sollte befuellt werden(optional)" << endl;
    }
    return 1;
}
int check::check_options(xml_parser::Options opti)///überpüft die Daten, welche zu dem options gemacht worden sind und ob notwendige Daten Fehlen
{
    int status = 1;
    if (opti.option.size() == 0)
    {
        cerr << "Es wurde keine Option zum Parsen hinterlegt!" << endl;
        return -1;
    }
    for (int i = 0; i < opti.option.size(); i++)
    {
        const int s = check_option(opti.option[i], i);
        if (!s)
        {
            status = -1;
        }
    }
    return status;
}
int check::check_option(xml_parser::Option opt, int i)///überpüft die Daten, welche zu der option gemacht worden sind und ob notwendige Daten Fehlen
{
    if (opt.shortOpt.empty() && opt.longOpt.empty())
    {
        cerr << "In Option " << i + 1 << " muss das Argument \"ShortOpt=\" oder \"LongOpt=\" gesetzt sein" << endl;
        return -1;
    }
    return 1;
}
