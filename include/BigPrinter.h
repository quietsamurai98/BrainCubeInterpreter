#ifndef BIGPRINTER_H
#define BIGPRINTER_H

#include <vector>
#include <deque>
#include <string>

class BigPrinter
{
    public:
        static std::string vect_to_string(std::vector<bool> &in_vect);
    private:
        static void minus_eq(std::deque<bool> &a, std::deque<bool> &b);
        static bool great_equal(std::deque<bool> &in_a, std::deque<bool> &in_b);
        static void divide_with_remainder(std::deque<bool> &numerator, std::deque<bool> &denominator, std::deque<bool> &quotient, std::deque<bool> &rem_in);
        static unsigned long long tou64(std::deque<bool> vect);
};

#endif // BIGPRINTER_H
