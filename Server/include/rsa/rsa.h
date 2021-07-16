#include <stdio.h>
#include <iostream>
#include <bitset>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


class Rsa
{
    unsigned long long p,q,e,n,d,euler,random;

    bool is_prime(unsigned long long number);
    public:
    
        Rsa();
};