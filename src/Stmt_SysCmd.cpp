#include "Stmt_SysCmd.h"
#include <iostream>
#include <string>
#include <vector>

Stmt_SysCmd::Stmt_SysCmd(char in_command)
{
    command = in_command;
}

Stmt_SysCmd::~Stmt_SysCmd()
{
    //dtor
}

void Stmt_SysCmd::run(){
    if(command == '#'){
        std::clog << "WARN: Debugging is not yet implemented" << std::endl;
    } else if(command == '!') {
        //Termination command
        std::exit(0);
    } else if(command == '?') {
        //Garbage collect command
        //Find all cells in memory with a value of zero, and purges them.

        for(auto it = begin(memory); it != end(memory);){
            if (it->second.to_bool()){
                ++it; //If cell is non-zero, skip it
            } else {
                it = memory.erase(it); //If cell is zero, erase it
            }
        }
        for(auto variable : variables){
            variables.at(variable.first).set_target_cell();
        }
    } else {
        //Only executed if the given command is unknown
        /**TODO: Add undefined system command exception**/
    }
}
