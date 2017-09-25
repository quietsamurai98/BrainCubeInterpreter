#ifndef CTRL_H
#define CTRL_H

#include "Expression.h"
#include <vector>
#include <string>
#include <memory>

class Ctrl : public Expression
{
    public:
        Ctrl();
        virtual ~Ctrl();
        virtual void run() = 0;
    protected:
        std::vector<std::unique_ptr<Expression>> expr_list; //List of expressions in the body of this control structure
        std::vector<std::string> scoped_names; //List of the names of pointers declared in this control structure, not including pointers declared in contained control structures.

        static bool parser_logging_enabled;

        void parse(std::string code); //Parses passed in code into a list of expressions
        void descope(); //Removes all the variables declared within this control structure from the variable map.

        void undeclared_var_as_controller(std::string ptrname);

        void add_Declare    (std::string ptrname);
        void add_PtrCmd     (std::string ptrname, std::string commands);
        void add_SysCmd     (char command);
        void add_CtrlIf     (std::string ptrname, std::string body);
        void add_CtrlWhile  (std::string ptrname, std::string body);
        void add_CtrlRepeat (std::string ptrname, std::string body);
    private:
};

#endif // CTRL_H
