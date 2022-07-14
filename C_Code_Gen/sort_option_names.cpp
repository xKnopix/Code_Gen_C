#include <iostream>
//#include "xml_parser.h"
#include <vector>
#include <algorithm> //zum sortieren

using namespace std;
//using namespace xercesc;

class Sort {

    public:
        //String a, string b = 2 Optionen
        bool compareFunction (std::string a, std::string b) {return a<b;} 


        int sort_options(string xml_datei) {

                
                std::string options[] = {"B","A","C","E","G","D","I","O"};

                std::vector<std::string> myvector (options, options+8); //create vector from array options

                std::sort(myvector.begin(),myvector.end(),compareFunction);//sort the vector

                //Ausgeben der Liste in alphabetischer Reihenfolge
                std::cout << "Sorted vector:";
                for (std::vector<std::string>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
                        std::cout << ' ' << *it;
                std::cout << '\n';

                return 0;
                }

        

};