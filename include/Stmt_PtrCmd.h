#ifndef STMT_PTRCMD_H
#define STMT_PTRCMD_H

#include "Expression.h"

class Stmt_PtrCmd : public Expression
{
    public:
        Stmt_PtrCmd(std::string in_name, std::string in_commands);
        virtual ~Stmt_PtrCmd();
        void run();
    protected:
        std::string name;
        std::string commands;
    private:
};

#endif // STMT_PTRCMD_H
