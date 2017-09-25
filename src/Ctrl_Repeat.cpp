#include "Ctrl_Repeat.h"

#include <string>
#include <cctype>

Ctrl_Repeat::Ctrl_Repeat(std::string in_ptrname, std::string in_body)
{
    ptrname = in_ptrname;
    parse(in_body);
}

Ctrl_Repeat::~Ctrl_Repeat()
{
    //dtor
}

void Ctrl_Repeat::run(){
    unsigned long long num_repeats = 0;
    bool is_num = true;
    for(char ch : ptrname){
        if(!std::isdigit(ch)){
            is_num = false;
        }
    }
    if(is_num){ //If ptrname is just a number
        num_repeats = std::stoull(ptrname);
    } else {
        try{
            num_repeats = variables.at(ptrname);
        } catch (const std::out_of_range& oor) {
            undeclared_var_as_controller(ptrname);
        }
    }
    for(unsigned long long repeat_counter = 0; repeat_counter < num_repeats; repeat_counter++){
        for(unsigned long long i = 0, l = expr_list.size(); i < l; i++){
            expr_list[i]->run();
        }
        descope();
    }
}
