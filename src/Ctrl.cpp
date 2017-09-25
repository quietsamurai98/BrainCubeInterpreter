#include "Ctrl.h"
#include "Stmt_Declare.h"
#include "Stmt_PtrCmd.h"
#include "Stmt_SysCmd.h"
#include "Ctrl_If.h"
#include "Ctrl_While.h"
#include "Ctrl_Repeat.h"
#include <vector>
#include <string>
#include <memory>
#include <cctype>
#include <iostream>

bool Ctrl::parser_logging_enabled;

Ctrl::Ctrl()
{
    //ctor
}

Ctrl::~Ctrl()
{
    //dtor
}

void Ctrl::parse(std::string code){
    unsigned long long i = 0;
    unsigned long long max_index = code.size();
    while(i < max_index) {
        if(code[i] == '~'){ //Declaration
            std::string ptrname;
            i++; //move to first letter of the pointer name

            bool has_alpha = false;
            bool all_chars_valid = true;

            while(code[i]!='~'){ //Add every character up until the ~ at the end of the declaration
                char ch = code[i];
                ptrname += ch;
                if(std::isalpha(ch)){
                    has_alpha = true;
                }
                if(!(std::isalnum(ch)||ch=='_')){ //If ch is not [A-Za-z_]
                    all_chars_valid = false;
                }
                i++;
            }

            if(has_alpha && all_chars_valid){
                add_Declare(ptrname);
            } else {
                /**Throw an InvalidPointerName Error**/
                std::clog << "[ERROR]\tParser: Invalid pointer name \""<<ptrname<<"\""<<std::endl;
                exit(1);
            }
        } else if (std::isalnum(code[i])||code[i]=='_') { //Pointer command
            std::string ptrname;
            while(code[i]!='('){
                ptrname += code[i];
                i++;
            }
            i++;
            std::string commands;
            while(code[i]!=')'){
                commands += code[i];
                i++;
            }
            add_PtrCmd(ptrname, commands);

        } else if (code[i] == '(') { //Control structure
            std::string ptrname;
            i++;
            while(code[i]!=')'){
                ptrname += code[i];
                i++;
            }
            i++;
            if(code[i]=='{') { //If structure
                unsigned long long nest_level = 1;
                std::string body;
                i++;
                while(nest_level){
                    if(code[i]=='{'){
                        nest_level++;
                    } else if(code[i]=='}'){
                        nest_level--;
                    }
                    if(nest_level){
                        body+=code[i];
                        i++;
                    }
                }
                add_CtrlIf(ptrname,body);
            } else if(code[i]=='[') { //While structure
                unsigned long long nest_level = 1;
                std::string body;
                i++;
                while(nest_level){
                    if(code[i]=='['){
                        nest_level++;
                    } else if(code[i]==']'){
                        nest_level--;
                    }
                    if(nest_level){
                        body+=code[i];
                        i++;
                    }
                }
                add_CtrlWhile(ptrname,body);

            } else if(code[i]=='(') { //Repeat structure
                unsigned long long nest_level = 1;
                std::string body;
                i++;
                while(nest_level){
                    if(code[i]=='('){
                        nest_level++;
                    } else if(code[i]==')'){
                        nest_level--;
                    }
                    if(nest_level){
                        body+=code[i];
                        i++;
                    }
                }
                add_CtrlRepeat(ptrname,body);

            }
        } else {
            add_SysCmd(code[i]);
        }
        i++;
    }
}

void Ctrl::descope(){
    for(unsigned long long i = 0; i < scoped_names.size(); i++){
        variables.erase(scoped_names[i]);
    }
    std::vector<std::string>().swap(scoped_names);
}

void Ctrl::undeclared_var_as_controller(std::string ptrname){
    std::cerr << std::endl << "RUNTIME ERROR: Attempted to use undeclared pointer "<<ptrname<<" as a control flow structure's controller!"<<std::endl;
    exit(1);
}

void Ctrl::add_Declare(std::string ptrname){
    expr_list.push_back(std::unique_ptr<Expression>(new Stmt_Declare(ptrname,scoped_names)));
    if(parser_logging_enabled)
        std::clog << "[INFO]\tParser: Added declaration for "<<ptrname<<std::endl;
}

void Ctrl::add_PtrCmd(std::string ptrname, std::string commands){
    expr_list.push_back(std::unique_ptr<Expression>(new Stmt_PtrCmd(ptrname,commands)));
    if(parser_logging_enabled)
        std::clog << "[INFO]\tParser: Added pointer command "<<ptrname<<"("<<commands<<")"<<std::endl;
}

void Ctrl::add_SysCmd(char command){
    expr_list.push_back(std::unique_ptr<Expression>(new Stmt_SysCmd(command)));
    if(parser_logging_enabled)
        std::clog << "[INFO]\tParser: Added system command '"<<command<<"'"<<std::endl;

}

void Ctrl::add_CtrlIf(std::string ptrname, std::string body){
    expr_list.push_back(std::unique_ptr<Expression>(new Ctrl_If(ptrname, body)));
    if(parser_logging_enabled)
        std::clog << "[INFO]\tParser: Added if statement ("<<ptrname<<"){"<<body<<"}"<<std::endl;
}

void Ctrl::add_CtrlWhile(std::string ptrname, std::string body){
    expr_list.push_back(std::unique_ptr<Expression>(new Ctrl_While(ptrname, body)));
    if(parser_logging_enabled)
        std::clog << "[INFO]\tParser: Added while statement ("<<ptrname<<")["<<body<<"]"<<std::endl;
}

void Ctrl::add_CtrlRepeat(std::string ptrname, std::string body){
    expr_list.push_back(std::unique_ptr<Expression>(new Ctrl_Repeat(ptrname, body)));
    if(parser_logging_enabled)
        std::clog << "[INFO]\tParser: Added repeat statement ("<<ptrname<<")("<<body<<")"<<std::endl;
}
