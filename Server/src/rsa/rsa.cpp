#include "rsa.h"

Rsa::Rsa()
{
    srand (time(NULL));
    random = rand();
    std::bitset<64> random_bits(random);
    random_bits[0]=1;
    random_bits[63]=1;
    std::cout<<"\n random: "<<random_bits<<std::endl;
    random=random_bits.to_ullong();
    std::cout<<"\n random: "<<random<<std::endl;
}

int main()
{
    Rsa t;

}