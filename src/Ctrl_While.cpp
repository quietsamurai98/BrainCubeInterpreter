#include "Ctrl_While.h"


Ctrl_While::Ctrl_While(std::string in_ptrname, std::string in_body)
{
    ptrname = in_ptrname;
    parse(in_body);
}

Ctrl_While::~Ctrl_While()
{
    //dtor
}

void Ctrl_While::run(){
    try{
        while(variables.at(ptrname)){
            for(unsigned long long i = 0, l = expr_list.size(); i < l; i++){
                expr_list[i]->run();
            }
            descope();
        }
    } catch (const std::out_of_range& oor) {
        undeclared_var_as_controller(ptrname);
    }
}
