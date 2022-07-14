#include <iostream>

using namespace std;

class Abstract{
    public:
        virtual void ueberschreiben() = 0;
};

class Klasse : public Abstract{
    public:
        void ueberschreiben(){
            cout << "überschrieben" << endl;
        } 
};

int main(){
    Klasse k;
    return 1;
} 

