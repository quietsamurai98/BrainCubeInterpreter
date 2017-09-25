#include "CellPointer.h"
#include "Cell.h"

#include <conio.h>
/** conio.h provides getch(), letting you get a char from CLI without a newline.
    This is not a standard library, and it will normally work on a Windows box.
    THIS IS A TERRIBLE WORKAROUND THAT ISN'T PORTABLE. FIX THIS ASAP.*/

#include <string>
#include <iostream>
#include <unordered_map>
#include <stdexcept>


CellPointer::CellPointer(std::unordered_map<std::string, Cell> *in_ram_ptr, std::string in_ptr_name){
	coord_x = 0;
	coord_y = 0;
	coord_z = 0;
	ptr_name = in_ptr_name;
	ram_ptr = in_ram_ptr;
	set_target_cell();
}

void CellPointer::move_r(){	  //  >   Move pointer right
	coord_x++;
	set_target_cell();
}
void CellPointer::move_l(){	  //  <   Move pointer left
    if(coord_x>0){
        coord_x--;
    } else {
        coord_x--;
        oob_err();
    }
    set_target_cell();
}
void CellPointer::move_u(){	  //  ^   Move pointer up
	coord_y++;
	set_target_cell();
}
void CellPointer::move_d(){	  //  v   Move pointer down
	if(coord_y>0){
        coord_y--;
    } else {
        coord_y--;
        oob_err();
    }
    set_target_cell();
}
void CellPointer::move_i(){	  //  X   Move pointer into the cube
	coord_z++;
	set_target_cell();
}
void CellPointer::move_o(){	  //  O   Move pointer out of the cube
	if(coord_z>0){
        coord_z--;
    } else {
        coord_z--;
        oob_err();
    }
    set_target_cell();
}

void CellPointer::edit_i(){	  //  +   Edit cell value by incrementing
    cell_ptr -> increment();
}
void CellPointer::edit_d(){	  //  -   Edit cell value by decrementing
    cell_ptr -> decrement();
}

void CellPointer::cono_c(){	  //  .   Output cell value console as character
    std::cout << cell_ptr -> to_char();
}
void CellPointer::cono_b(){	  //  '   Output cell value console as binary
    std::cout << cell_ptr -> to_binary() << std::endl;
}
void CellPointer::cono_d(){	  //  :   Output cell value console as decimal
    std::cout << cell_ptr -> to_decimal() << std::endl;
}

void CellPointer::coni_c(){	  //  ,   Set cell value to character from console
    char ch = (char) getch(); /**FIND A BETTER WAY TO DO THIS**/
    cell_ptr -> from_char(ch);
}
void CellPointer::coni_b(){	  //  "   Set cell value to binary from console
    std::string line;
    std::getline(std::cin, line);
    cell_ptr -> from_binary(line);
}
void CellPointer::coni_d(){	  //  ;   Set cell value to decimal from console
    std::string line;
    std::getline(std::cin, line);
    cell_ptr -> from_decimal(line);
}

void CellPointer::set_target_cell(){
    std::string key = std::to_string(coord_x)+","+std::to_string(coord_y)+","+std::to_string(coord_z);
    if(ram_ptr -> find(key) == ram_ptr -> end()){    //If the target cell does not exist
        allocate_cell();     //Make a new cell
    }
    cell_ptr = &ram_ptr -> at(key);
}

void CellPointer::allocate_cell(){
    std::string key = std::to_string(coord_x)+","+std::to_string(coord_y)+","+std::to_string(coord_z);
    try{
        if(ram_ptr -> find(key) == ram_ptr -> end()){ //If cell does not exist
            Cell cell(coord_z+1);   //Make a new cell
            std::pair<std::string, Cell> temp(key,cell);    //Make a <key,obj> pair
            ram_ptr -> insert(temp);    //Add the cell to the list
        }
    } catch (...) {
        std::cerr << "RUNTIME ERROR: Could not create cell ["<<coord_z<<"]["<<coord_y<<"]["<<coord_x<<"]"<<std::endl;
        std::cerr << "Aborting execution..." << std::endl;
        std::exit(1);
    }
}

void CellPointer::oob_err(){
    std::cerr << "OUT OF BOUNDS ERROR" << std::endl;
    std::cerr << "\tPointer \""<<ptr_name<<"\" Attempted to move to an invalid position." <<std::endl;
    std::cerr << "\t\tPosition in question, formatted as [Sheet][Tape][Cell]:"<<std::endl;
    std::cerr << "\t\t["<<coord_z<<"]["<<coord_y<<"]["<<coord_x<<"]" << std::endl;
    std::cerr << "Aborting execution..." << std::endl;
    std::exit(1);
}

CellPointer::operator bool(){  //Convert to boolean for if and while control flow structures
    return this -> cell_ptr -> to_bool();
}
CellPointer::operator signed short(){    //Convert to u64 for repeat control flow structures
    return (signed short)(this -> cell_ptr -> to_u64());
}
CellPointer::operator signed int(){    //Convert to u64 for repeat control flow structures
    return (signed int)(this -> cell_ptr -> to_u64());
}
CellPointer::operator signed long(){    //Convert to u64 for repeat control flow structures
    return (signed long)(this -> cell_ptr -> to_u64());
}
CellPointer::operator signed long long(){    //Convert to u64 for repeat control flow structures
    return (signed long long)(this -> cell_ptr -> to_u64());
}
CellPointer::operator unsigned short(){    //Convert to u64 for repeat control flow structures
    return (unsigned short)(this -> cell_ptr -> to_u64());
}
CellPointer::operator unsigned int(){    //Convert to u64 for repeat control flow structures
    return (unsigned int)(this -> cell_ptr -> to_u64());
}
CellPointer::operator unsigned long(){    //Convert to u64 for repeat control flow structures
    return (unsigned long)(this -> cell_ptr -> to_u64());
}
CellPointer::operator unsigned long long(){    //Convert to u64 for repeat control flow structures
    return this -> cell_ptr -> to_u64();
}
