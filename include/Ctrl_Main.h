#ifndef CTRL_MAIN_H
#define CTRL_MAIN_H

#include "Ctrl.h"
#include <vector>
#include <string>
#include <memory>

class Ctrl_Main : public Ctrl
{
    public:
        Ctrl_Main(std::string body, bool in_parser_logging_enabled);
        virtual ~Ctrl_Main();
        void run();
    protected:
        std::string sanitize(std::string code);
    private:
};

#endif // CTRL_MAIN_H
