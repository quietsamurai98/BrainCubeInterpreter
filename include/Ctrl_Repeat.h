#ifndef CTRL_REPEAT_H
#define CTRL_REPEAT_H

#include "Ctrl.h"

#include <string>

class Ctrl_Repeat : public Ctrl
{
    public:
        Ctrl_Repeat(std::string in_ptrname, std::string in_body);
        virtual ~Ctrl_Repeat();
        void run();
    protected:
        std::string ptrname;

    private:
};

#endif // CTRL_REPEAT_H
