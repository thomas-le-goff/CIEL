#pragma once

#include <string>
#include <random>

class CryptoMonster
{
private:
    static std::string generateRandom18DigitNumber();

    int getDnaPart(int index, int size) const;

public:
    CryptoMonster();
    ~CryptoMonster() = default;

    int getNumberOfEyes() const;

    void describe() const;
};
