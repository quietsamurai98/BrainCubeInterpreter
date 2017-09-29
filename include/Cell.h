#ifndef CELL_H
#define CELL_H
#include <vector>
#include <string>

class Cell
{
    public:
        Cell(unsigned long long bit_count); //sheet_index is the index of the cell's sheet, and is used to determine the maximum number of bits the cell can hold.
        Cell(Cell *other); //copy constructor
        ~Cell();
        unsigned long long to_u64(); //converts to a primitive u64
        bool to_bool(); //returns value!=0
        //The following are used for console IO
        std::string to_char();      //Returns a string containing the character with ASCII value = cell value mod 256
        std::string to_binary();    //Returns a string containing the binary representation of the cell's value, with the least significant bit on the right.
        std::string to_decimal();   //Returns a string containing the base 10 representation of the cell's value
        void from_char(char ch);                //Sets the cell's value to the ASCII value of ch
        void from_binary(std::string bin_str);  //Sets the cell's value to the value of the base two number contained in bin_str
        void from_decimal(std::string dec_str); //Sets the cell's value to the value of the base 10 number contained in dec_str

        //The following are used for cell data manipulation
        void increment();   //Increases the value of the cell by 1
        void decrement();   //Decreases the value of the cell by 1

        /*
        Cell operator=(Cell that);  // my_cell = your_cell
        Cell operator++();          // ++my_cell
        Cell operator++(int);       // my_cell++
        Cell operator--();          // --my_cell
        Cell operator--(int);       // my_cell--
        */
    protected:
        std::vector<bool> bit_list; //The binary representation of the cells value. The least significant bit is located at bit_list[0]
        unsigned long long int max_bits; //The maximum number of bits this cell can hold before overflowing
};

#endif // CELL_H
