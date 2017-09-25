#include "Stmt_Declare.h"
#include <vector>
#include <string>

Stmt_Declare::Stmt_Declare(std::string in_name, std::vector<std::string> &scoped_names)
{
    //ctor
    name = in_name;
    scoped_names_ref = &scoped_names;
}

Stmt_Declare::~Stmt_Declare()
{
    //dtor
}

void Stmt_Declare::run(){
    variables.emplace(name,CellPointer(&memory, name));
    scoped_names_ref -> push_back(name);
}
