#include <iostream>
//#include <options.h>

//#include "xml_parser.h"
//#include <xercesc/parsers/XercesDOMParser.hpp>
//#include <xercesc/dom/DOM.hpp>
//#include <xercesc/sax/HandlerBase.hpp>
//#include <xercesc/util/XMLString.hpp>
//#include <xercesc/util/PlatformUtils.hpp>

#include <QtGui>
//Braucht man für Blockformatierung


using namespace std;
//using namespace xercesc;

class Help {
    public:
        string user_input; //Input des Users, der nach Hilfe fordert
    
    protected:
        virtual void printHelp() {

            //Methode, die den Hilfetext aus der .xml auf der Konsole ausgibt

            std::cout << "Diesen Hilfetext ausgeben."; //Nur vorübergehend, da Probleme mit xml_parser
        };
        
        // Funktion zur Blockformatierung
        void insertAlignedText(int row, QString text)
            {

               
            text = textCursor.blockFormat();

            // Read vertical part of current alignment flags
            Qt::Alignment vertAlign = blockFormat.alignment() & Qt::AlignVertical_Mask;

            // Mask out vertical part of specified alignment flags
            Qt::Alignment horzAlign = alignment & Qt::AlignHorizontal_Mask;

            // Combine current vertical and specified horizontal alignment
            Qt::Alignment combAlign = horzAlign | vertAlign;

            // Apply and write
            blockFormat.setAlignment(combAlign);    
            textCursor.setBlockFormat(blockFormat);
            textCursor.insertText(text);
        };

        //Funktion, sodass nur 79 Zeichen pro Zeile sind
        void sign_lenght() {

                //Schleife, die Zeichen mitzählt
                for (int i=0, j=1; i<=127; i++,j++)
                    {
                        int x = i;
                        char y = (char) x;
                        cout << y;

                        //Zeilenumbruch bei dem 80. Zeichen
                        if (j == 80) {
                            j = 0;
                            cout << '\n';
                        }
                    }

        };


        //xml-Reqs konnte ich leider nicht machen, da xerces bei mir spinnt



        
};
