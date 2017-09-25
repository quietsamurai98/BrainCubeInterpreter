#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Ctrl_Main.h"

using namespace std;

int main()
{
    cout << "Enable parser logging? [Y/n] ";
    string in_Yn;
    getline(cin,in_Yn);
    bool parser_logging_enabled = (in_Yn[0] == 'Y' || in_Yn[0] == 'y');
    ifstream file;
    string filename = "";
    do{
        cout << "Enter path to BrainCube source file: ";
        getline(cin, filename);
        file.open(filename);
        if(file.bad()){
            cout << "File \""<<filename<<"\" could not be opened. Please try again." << endl;
        }
    } while(file.bad());

    stringstream buffer;
    buffer << file.rdbuf();
    string code = buffer.str();
    Ctrl_Main mymain(code, parser_logging_enabled);
    mymain.run();
}
