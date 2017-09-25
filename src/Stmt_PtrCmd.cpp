#include "Stmt_PtrCmd.h"
#include "CellPointer.h"
#include <string>
#include <iostream>
#include <stdexcept>

Stmt_PtrCmd::Stmt_PtrCmd(std::string in_name, std::string in_commands)
{
    //ctor
    name = in_name;
    commands = in_commands;
}

Stmt_PtrCmd::~Stmt_PtrCmd()
{
    //dtor
}

void Stmt_PtrCmd::run(){
    try{
        CellPointer *ptr = &variables.at(name);
        for(unsigned long long i = 0; i < commands.size(); i++){
            char c = commands[i];
            if(c =='<'){ ptr->move_l();  } else
            if(c =='>'){ ptr->move_r();  } else
            if(c =='^'){ ptr->move_u();  } else
            if(c =='v'){ ptr->move_d();  } else
            if(c =='X'){ ptr->move_i();  } else
            if(c =='O'){ ptr->move_o();  } else
            if(c =='+'){ ptr->edit_i();  } else
            if(c =='-'){ ptr->edit_d();  } else
            if(c =='.'){ ptr->cono_c();  } else
            if(c=='\''){ ptr->cono_b();  } else
            if(c ==':'){ ptr->cono_d();  } else
            if(c ==','){ ptr->coni_c();  } else
            if(c =='"'){ ptr->coni_b();  } else
            if(c ==';'){ ptr->coni_d();  } else
            {
                //This block is only executed if the given pointer command is undefined.
                std::cerr << "RUNTIME ERROR: Attempted to perform unknown operation "<<c<<" upon pointer "<<name<<"."<<std::endl;
                std::exit(1);
            }
        }
    } catch (const std::out_of_range& oor) {
        std::cerr << "RUNTIME ERROR: Attempted to perform operations upon undeclared pointer "<<name<<"."<<std::endl;
        std::exit(1);
    }
}
