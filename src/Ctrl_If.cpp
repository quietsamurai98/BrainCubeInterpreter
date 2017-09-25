#include "Ctrl_If.h"

Ctrl_If::Ctrl_If(std::string in_ptrname, std::string in_body)
{
    ptrname = in_ptrname;
    parse(in_body);
}

Ctrl_If::~Ctrl_If()
{
    //dtor
}

void Ctrl_If::run(){
    try{
        if(variables.at(ptrname)){
            for(unsigned long long i = 0, l = expr_list.size(); i < l; i++){
                expr_list[i]->run();
            }
            descope();
        }
    } catch (const std::out_of_range& oor) {
        undeclared_var_as_controller(ptrname);
    }
}
