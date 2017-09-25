#ifndef STMT_DECLARE_H
#define STMT_DECLARE_H

#include "Expression.h"
#include <vector>
#include <string>

class Stmt_Declare : public Expression
{
    public:
        Stmt_Declare(std::string name, std::vector<std::string> &scoped_names);
        virtual ~Stmt_Declare();
        void run();
    protected:
        std::vector<std::string> *scoped_names_ref;
        std::string name;
    private:
};

#endif // STMT_DECLARE_H
