#include "BigPrinter.h"

#include <string>
#include <vector>
#include <deque>

unsigned long long BigPrinter::tou64(std::deque<bool> vect){
    unsigned long long sum = 0ULL;
    for(unsigned char i=0; i<64 && i<vect.size(); ++i){ //Loop over the bits
        if(vect[i]){
            sum |= 1ULL << (unsigned long long)i;       //add bit_list[i]*2^i to sum
        }
    }
    return sum;
}

bool BigPrinter::great_equal(std::deque<bool> &in_a, std::deque<bool> &in_b){
	std::deque<bool> a(in_a);
	std::deque<bool> b(in_b);

	unsigned long long a_size = a.size();
	unsigned long long b_size = b.size();
	while(b_size && !b[b_size-1]){
        b_size--;
	}
	while(a_size && !a[a_size-1]){
        a_size--;
	}
	if(a_size > b_size){
		return true;
	} else if (a_size < b_size){
		return false;
	} else {
		for(unsigned long long i = a_size; i > 0; i--){
            i--;
			if( a[i] != b[i] ) {
				return a[i];
			}
            i++;
		}
		return true;
	}
}

void BigPrinter::minus_eq(std::deque<bool> &a, std::deque<bool> &b){
	unsigned long long a_size = a.size();
	unsigned long long b_size = b.size();
	while(b_size && !b[b_size-1]){
        b_size--;
	}
	while(a_size && !a[a_size-1]){
        a_size--;
	}
	for(unsigned long long i = 0; i < b_size; i++){
		if(b[i]){
			if(a[i]){
				a[i] = false;
			} else {
				unsigned long long j = i;
				while(!a[j]){
					a[j]= true;
					j++;
				}
				a[j] = false;
			}
		}
	}
}


void BigPrinter::divide_with_remainder(
	std::deque<bool> &numerator,
	std::deque<bool> &denominator,
	std::deque<bool> &quotient,
	std::deque<bool> &rem_in
){
    auto n_size = numerator.size();
    while(n_size && !numerator[n_size-1]){
        n_size--;
	}
	std::deque<bool>(n_size).swap(quotient);
	std::deque<bool> remainder;
	remainder.push_back(false);

	for(unsigned long long i = n_size; i > 0; i--){
        i--;
		remainder.push_front(numerator.at(i)); //Left-shift remainder by 1 bit, set least significant bit to numerator[i]
		if( great_equal(remainder, denominator) ){
			minus_eq(remainder, denominator);
			quotient.at(i) = true;
		}
        i++;
	}
	auto r_size = remainder.size();
    while(r_size && !remainder[r_size-1]){
        r_size--;
	}
	std::deque<bool>(r_size).swap(rem_in);
	for(unsigned long long i = 0; i < r_size; i++){
        rem_in.at(i) = remainder.at(i);
	}
}

std::string BigPrinter::vect_to_string(std::vector<bool> &in_vect){
    std::deque<bool> num;
    bool is_zero = true;
    for(unsigned long long i = 0; i < in_vect.size(); i++){
        num.push_back(in_vect.at(i));
        if(in_vect.at(i)){
            is_zero = false;
        }
    }

    if(is_zero){
        return "0";
    }
    while(!num.back()){
        num.pop_back();
    }

    bool den_arr[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,1,1,0,0,0,1,0,0,1,1,1,0,0,0,1,1,0,1,0,1,0,0,0,1};
    std::deque<bool> den(den_arr, den_arr+64);

    std::deque<bool> q;
    std::deque<bool> r;

    std::string digits;

    while(num.size()){
        divide_with_remainder(num, den, q, r);
        std::string digit = std::to_string(tou64(r));
        while(digit.size()<19){
            digit = "0"+digit;
        }
        digits=digit+digits;
        q.swap(num);
    }
    while(digits[0]=='0'){
        digits.erase(0,1);
    }
    return digits;
}
