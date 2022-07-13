#include "TestsNewFile.h"

using namespace noNameSpace;


class MyOptionParser : public noNameSpace::noClassname{
public:

void hallo(bool b)
{
    cout << "hallo" << endl;
}
};



int main(int argc, char *argv[])
{
    noClassname p;

    p.parse(argc, argv);
}