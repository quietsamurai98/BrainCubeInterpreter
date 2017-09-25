#ifndef CELLPOINTER_H
#define CELLPOINTER_H

#include "Cell.h"
#include <unordered_map>

class CellPointer
{
    public:
        CellPointer(std::unordered_map<std::string, Cell> *in_ram_ptr, std::string in_ptr_name);

        operator bool(); //Convert to boolean for if and while control flow structures

        //Convert to various integers.
        operator signed short();
        operator signed int();
        operator signed long();
        operator signed long long();
        operator unsigned short();
        operator unsigned int();
        operator unsigned long();
        operator unsigned long long();

        /** BRAINCUBE POINTER COMMANDS **/
        /*  The following functions directly correspond to a BrainCube pointer command. */
        void move_l();  //  <   Move pointer left
        void move_r();  //  >   Move pointer right
        void move_u();  //  ^   Move pointer up
        void move_d();  //  v   Move pointer down
        void move_i();  //  X   Move pointer into the cube
        void move_o();  //  O   Move pointer out of the cube

        void edit_i();  //  +   Edit cell value by incrementing
        void edit_d();  //  -   Edit cell value by decrementing

        void cono_c();  //  .   Output cell value console as character
        void cono_b();  //  '   Output cell value console as binary
        void cono_d();  //  :   Output cell value console as decimal

        void coni_c();  //  ,   Set cell value to character from console
        void coni_b();  //  "   Set cell value to binary from console
        void coni_d();  //  ;   Set cell value to decimal from console

        void set_target_cell(); //Public so it can be used by the GC.
    protected:

    private:
        unsigned long long coord_x;
        unsigned long long coord_y;
        unsigned long long coord_z;
        std::string ptr_name;
        std::unordered_map<std::string, Cell> *ram_ptr;
        Cell *cell_ptr;

        void allocate_cell();
        void oob_err();
};

#endif // CELLPOINTER_H
