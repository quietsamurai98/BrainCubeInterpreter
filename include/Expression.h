#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <unordered_map>
#include <string>
#include "Cell.h"
#include "CellPointer.h"

class Expression
{
    public:
        virtual ~Expression() {};
        virtual void run() = 0; /**executes the expression**/

        static std::unordered_map<std::string, Cell> memory;            /**Shared MemoryCube**/
        static std::unordered_map<std::string, CellPointer> variables;  /**All CellPointers that have been declared, and are still in scope.**/
    protected:

    private:
};
#endif // EXPRESSION_H
