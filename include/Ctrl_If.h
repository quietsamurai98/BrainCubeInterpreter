#ifndef CTRL_IF_H
#define CTRL_IF_H

#include "Ctrl.h"

#include <string>

class Ctrl_If : public Ctrl
{
    public:
        Ctrl_If(std::string in_ptrname, std::string in_body);
        virtual ~Ctrl_If();
        void run();
    protected:
        std::string ptrname;

    private:
};

#endif // CTRL_IF_H
