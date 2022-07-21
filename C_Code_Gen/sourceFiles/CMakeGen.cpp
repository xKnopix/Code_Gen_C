//Autor: Michael Hornstein

#include "../headerFiles/CMakeGen.h"

CMakeGen::CMakeGen(xml_parser::GetOptSetup data){
    GenHeader();//setze String zusammen
    GenAddExecutable(data.headerFileName, data.sourceFileName);//setze String zusammen
    GenTail();//setze String zusammen

    std::ofstream MyFile("CMakeLists.txt");
    MyFile << this->output;//schreibe String in CMakeLists.txt
    MyFile.close();
}

void CMakeGen::GenHeader(){
    this->output.append("cmake_minimum_required(VERSION 3.8)\n");
    this->output.append("project(\"ExampleMain\")\n");
}

void CMakeGen::GenAddExecutable(xml_parser::HeaderFileName header, xml_parser::SourceFileName source){
    this->output.append("add_executable (ExampleMain \"exampleMain.cpp\" \"");
    this->output.append(header.content);
    this->output.append("\" \"");
    this->output.append(source.content);
    this->output.append("\")\n");
    
}

void CMakeGen::GenTail(){
    this->output.append("if (CMAKE_VERSION VERSION_GREATER 3.12)\n");
    this->output.append("\tset_property(TARGET ExampleMain PROPERTY CXX_STANDARD 20)\n");
    this->output.append("endif()");
}
