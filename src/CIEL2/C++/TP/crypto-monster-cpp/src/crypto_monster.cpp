#include "crypto_monster.hpp"
#include <iostream>

std::string CryptoMonster::generateRandom18DigitNumber()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<uint64_t> dist(
        100000000000000000ULL, // 10^17
        999999999999999999ULL  // 10^18 - 1
    );

    return std::to_string(dist(gen));
}

CryptoMonster::CryptoMonster()
{
}

int CryptoMonster::getDnaPart(int index, int size) const
{
    return 1;
}

int CryptoMonster::getNumberOfEyes() const
{
    return 1;
}

void CryptoMonster::describe() const
{
    std::cout << "My number of eyes is: " << this->getNumberOfEyes() << std::endl;
}
