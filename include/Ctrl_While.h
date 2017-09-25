#ifndef CTRL_WHILE_H
#define CTRL_WHILE_H

#include "Ctrl.h"

#include <string>

class Ctrl_While : public Ctrl
{
    public:
        Ctrl_While(std::string in_ptrname, std::string in_body);
        virtual ~Ctrl_While();
        void run();
    protected:
        std::string ptrname;

    private:
};

#endif // CTRL_WHILE_H
