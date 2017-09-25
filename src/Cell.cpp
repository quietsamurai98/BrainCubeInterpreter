#include "Cell.h"
#include <vector>
#include <string>

/**
 *  TODO: ADD THEORETICAL SUPPORT FOR CELLS WITH A VALUE OF OVER 2^9223372036854775808-1
 *      Yes, I know it would take 16 exbibytes of RAM to store that value.
 *      However, 20 years ago, 16 gigabytes of RAM was ludicrously huge, and look at us now.
 *
 *  TODO: ADD to_integer AND from_integer SUPPORT FOR VALUES OF OVER 2^64-1
 *      Currently:
 *          to_integer works by using the first 64 bits of bit_list to bit-twiddle an unsigned long long
 *          from_integer works by using std::string.stoull()
 **/

Cell::Cell(unsigned long long param_max_bits)
{
    max_bits = param_max_bits;
    std::vector<bool>(max_bits).swap(bit_list); //Set bit_list to a vector<bool> with max_bits elements
}

Cell::~Cell(){
    std::vector<bool>().swap(bit_list);
}

unsigned long long Cell::to_u64(){
    unsigned long long sum = 0;
    for(unsigned char i=0; i<64 && i<(this->bit_list.size()); ++i){ //Loop over the bits
        sum |= (this->bit_list[i]) << i;       //add bit_list[i]*2^i to sum
    }
    return sum;
}

bool Cell::to_bool(){
    for(bool b : bit_list){ //Loop over the bits
        if(b){
            return b;
        }
    }
    return false;
}

std::string Cell::to_char()
{
    char ch = 0;
    for(char i=0; i<8 && i<(char)(this->bit_list.size()); ++i){ //Loop over the 8 (if they exist) least significant bits, in ascending order of significance
        ch = (char)(ch|((this->bit_list[i]) << i));       //add the bit from bit list to the appropriate bit in ch
    }
    return std::string({ch});   //wrap ch in a string and return it
}

std::string Cell::to_binary()
{


    std::string str;
    for(unsigned long long i = 0; i < this->bit_list.size(); i++){
        str=((this->bit_list[i])?("1"):("0"))+str;
    }
    return str;
}

std::string Cell::to_decimal()
{
    unsigned long long sum = 0;
    for(unsigned char i=0; i<64 && i<(this->bit_list.size()); ++i){ //Loop over the bits
        sum |= (this->bit_list[i]) << i;       //add bit_list[i]*2^i to sum
    }
    return std::to_string(sum);
}

void Cell::from_char(char ch)
{
    std::vector<bool>(this->max_bits).swap(this->bit_list); //Reset bit_list to zero
    for (unsigned char i=0; i < 8 && i < this->max_bits; ++i){
        this->bit_list[i] = (ch & (1<<i)) != 0; //Set each bit of bit_list to the corresponding bit in ch
    }
}

void Cell::from_binary(std::string str)
{

    std::vector<bool>(this->max_bits).swap(this->bit_list); //Reset bit_list to zero
    for (unsigned long long i=0; i < this->max_bits; ++i){
        this->bit_list[i] = (str[str.length()-i-1]=='0')?false:true;
    }
}

void Cell::from_decimal(std::string str)
{
    unsigned long long num = std::stoull(str);
    std::vector<bool>(this->max_bits).swap(this->bit_list); //Reset bit_list to zero
    for (unsigned long long i=0; i < this->max_bits; ++i){
        this->bit_list[i] = (num & (1<<i)) != 0; //Set each bit of bit_list to the corresponding bit in num
    }
}

void Cell::increment()
{
    unsigned long long i = 0;
    while(this->bit_list[i] && i < this->max_bits){
        this->bit_list[i] = false;
        i++;
    }
    if(i < this->max_bits){
        this->bit_list[i] = true;
    }
}

void Cell::decrement()
{
    unsigned long long i = 0;
    while(!this->bit_list[i] && i < this->max_bits){
        this->bit_list[i] = true;
        i++;
    }
    if(i < this->max_bits){
        this->bit_list[i] = false;
    }
}
