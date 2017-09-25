#include "Ctrl_Main.h"
#include "Stmt_Declare.h"
#include "Stmt_PtrCmd.h"
#include <string>
#include <iostream>

Ctrl_Main::Ctrl_Main(std::string code, bool in_parser_logging_enabled)
{
    //ctor
    parser_logging_enabled = in_parser_logging_enabled;
    code = sanitize(code);
    parse(code);
}

Ctrl_Main::~Ctrl_Main()
{
    //dtor
}

void Ctrl_Main::run(){
    for(unsigned long long i = 0, l = expr_list.size(); i < l; i++){
        expr_list[i]->run();
    }
    descope();
}

std::string Ctrl_Main::sanitize(std::string code){
    std::string clean_code;
    unsigned long long i = 0;
    unsigned long long max_index = code.size();
    while(i < max_index) {
        if(code[i]=='/'&&code[i+1]=='*'){ //Skip over comment
            while(!(code[i]=='*'&&code[i+1]=='/')){
                i++;
            }
            i+=2;
        } else if (code[i]==' '||code[i]=='\t'||code[i]=='\v'||code[i]=='\r'||code[i]=='\n') {
            i++;
        } else {
            clean_code += code[i];
            i++;
        }
    }
    if(parser_logging_enabled){
        std::clog << "[INFO]\tParser: Code has been sanitized." << std::endl;
        std::clog << "[INFO]\tParser: Sanitized code: " << std::endl << clean_code << std::endl;
    }
    return clean_code;
}
