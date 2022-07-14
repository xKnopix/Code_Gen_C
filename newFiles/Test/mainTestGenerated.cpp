#include "TestsNewFile.h"


class MyOptionParser : public noClassname{

public:

void hallo(bool b)
{
    cout << "hallo" << endl;
}

};



int main(int argc, char *argv[])
{
    MyOptionParser p;

    cout << argc << endl;
    cout << argv[1]  << endl;

    p.hallo(false);
    p.parse(argc, argv);
    cout << p.getValueOfsignperline();
}
