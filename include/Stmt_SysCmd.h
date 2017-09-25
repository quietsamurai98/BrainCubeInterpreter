#ifndef STMT_SYSCMD_H
#define STMT_SYSCMD_H

#include "Expression.h"

class Stmt_SysCmd : public Expression
{
    public:
        Stmt_SysCmd(char in_command);
        virtual ~Stmt_SysCmd();
        void run();
    protected:
        char command;

    private:
};

#endif // STMT_SYSCMD_H
