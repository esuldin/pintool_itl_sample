#include <iostream>

#include "../pi/pi.h"


int main()
{
    const unsigned int iter_num = 25;

    std::cout << "builtin_constant() returned: " << builtin_constant() << std::endl;
    std::cout << "viete_formula() returned: " << viete_formula(iter_num) << std::endl;
    std::cout << "wallis_formula() returned: " << wallis_formula(iter_num) << std::endl;
}