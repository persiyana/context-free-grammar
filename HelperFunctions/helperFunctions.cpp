#include <cmath>
#include <cstring>

#include "helperFunctions.hpp"

unsigned HelperFunctions::getNextPowerOfTwo(unsigned num)
{
    if (num == 0)
    {
        return 1;
    }
    
    if ((num & (num - 1)) == 0)
    {
        return num << 1;
    }
    
    return 1 << (unsigned)ceil(log2(num));
}